#include <syscalls.h>
#include <commands/commands.h>
#include <string.h>
#include <ansii.h>

void cmd_unknown(const char *cmd, long cmd_len) {
    (void)cmd; (void)cmd_len;

    syscall_write(1, cmd, cmd_len);
    syscall_write(1, LIGHT_GRAY_FG, strlen(LIGHT_GRAY_FG));
    syscall_write(1, ": ", 2);
    syscall_write(1, RESET, strlen(RESET));
    syscall_write(1, "Unknown command\n", strlen("Unknown command\n"));
}