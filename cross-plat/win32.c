#include "platform.h"

#define WINAPI __stdcall
#define LPCSTR const char*
#define UINT unsigned int
#define HWND void*

__declspec(dllimport)
int WINAPI MessageBoxA(HWND, LPCSTR, LPCSTR, UINT);

__declspec(dllimport)
void WINAPI ExitProcess(unsigned int);

void platform_print_hello(void)
{
    MessageBoxA(0, "Hello World", "Hello", 0);
}

void platform_exit(int code)
{
    ExitProcess(code);
}
