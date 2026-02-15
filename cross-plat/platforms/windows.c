#include <windows.h>
#include "platforms.h"

OS_ARCH getOS() {
    return WINDOWS;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MessageBox(NULL, "WOW", "Cool", NULL);
    return program_entry();
}