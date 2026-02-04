#include "platform.h"

#define SYS_write 1
#define SYS_exit 60

static inline long syscall(long n, long a, long b, long c)
{
    long ret;
    __asm__ volatile (
        "syscall"
        : "=a"(ret)
        : "a"(n), "D"(a), "S"(b), "d"(c)
        : "rcx", "r11", "memory"
    );
    return ret;
}

void platform_print_hello(void)
{
    const char msg[] = "Hello World\n";
    syscall(SYS_write, 1, (long)msg, sizeof(msg)-1);
}

void platform_exit(int code)
{
    syscall(SYS_exit, code, 0, 0);
}
