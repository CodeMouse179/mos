#if defined(_WIN32)
#define SYSTEM_WINDOWS 1
#endif
#if defined(__linux__)
#define SYSTEM_LINUX 1
#endif
#if defined(__APPLE__)
#define SYSTEM_MACOS 1
#endif
#if defined(SYSTEM_LINUX) || defined(SYSTEM_MACOS)
#define SYSTEM_POSIX 1
#endif
#if defined(_MSC_VER)
#define MICROSOFT_COMPILER 1
#endif

#define null ((void*)0)
#define true 1
#define false 0

typedef int bool;
typedef char byte;
typedef void (*on_key_input)(int, int);

bool init();
bool deinit();
void print(const char* str);
int char_to_int(char ch);
int str_len(const char* str);

#if defined(MICROSOFT_COMPILER)
#pragma execution_character_set("utf-8")
#endif

int char_to_int(char ch)
{
    int n = ch - 48;
    if (n < 0 || n > 9) return -1;
    return n;
}

int str_len(const char* str)
{
    int length = 0;
    while (*str)
    {
        length++;
        str++;
    }
    return length;
}

#if defined(SYSTEM_WINDOWS)
#include <Windows.h>
int console_output_cp = 0;
bool init()
{
    console_output_cp = GetConsoleOutputCP();
    if (console_output_cp == 0) return false;
    BOOL ret = SetConsoleOutputCP(CP_UTF8);
    return ret;
}
bool deinit()
{
    BOOL ret = SetConsoleOutputCP(console_output_cp);
    return ret;
}
void print(const char* str)
{
    HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (std_output_handle == INVALID_HANDLE_VALUE || std_output_handle == NULL) return;
    DWORD written;
    WriteConsoleA(std_output_handle, str, str_len(str), &written, NULL);
}
#endif

#if defined(SYSTEM_POSIX)
#include <unistd.h>
bool init()
{
    return true;
}
bool deinit()
{
    return true;
}
void print(const char* str)
{
    write(STDOUT_FILENO, str, str_len(str));
}
#endif

int main(int argc, char** argv)
{
    init();
    print("你好，世界😄hello, world\n");
    deinit();
    return 0;
}