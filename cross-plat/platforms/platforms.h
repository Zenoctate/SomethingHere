#ifndef PLATFORMS
#define PLATFORMS

typedef int OS_ARCH;

#define LINUX_KERNEL 1
#define WINDOWS 2


OS_ARCH getOS();
int program_entry();

void make_UI();
void handle_UI_events();
void update_UI();

#endif