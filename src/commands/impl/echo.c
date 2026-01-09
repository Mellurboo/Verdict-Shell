#include <syscalls.h>
#include <printf.h>

void cmd_echo(const char *args, long args_len) {
    (void)args_len;
    printf("%s\n", args);
}