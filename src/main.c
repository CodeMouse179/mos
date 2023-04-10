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
int main()
{
    return 0;
}