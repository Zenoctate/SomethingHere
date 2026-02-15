#include "platforms.h"

OS_ARCH getOS() {
    return LINUX_KERNEL;
}

int main() {
    return program_entry();
}