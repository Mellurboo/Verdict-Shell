#include <syscalls.h>

void cmd_clear(const char *args, long args_len) {
    (void)args; (void)args_len;
    syscall_clear(1);
}