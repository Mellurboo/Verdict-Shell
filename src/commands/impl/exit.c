#include <syscalls.h>

void cmd_exit(const char *args, long args_len) {
    (void)args; (void)args_len;
    syscall_exit(0);
}