#include <syscalls.h>
#include <exit.h>

void cmd_exit() {
    _exit(0);
}