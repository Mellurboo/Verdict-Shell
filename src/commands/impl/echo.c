#include <syscalls.h>

void cmd_echo(const char *args, long args_len) {
    syscall_write(1, args, args_len);
    syscall_write(1, "\n", 1);
}