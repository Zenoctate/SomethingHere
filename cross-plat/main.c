#include "platform.h"

void program_entry(void)
{
    platform_print_hello();
    platform_exit(0);
}

#ifdef _WIN32
void WinMainCRTStartup(void)
#else
void _start(void)
#endif
{
    program_entry();
}