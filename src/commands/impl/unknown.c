#include <syscalls.h>
#include <commands/commands.h>
#include <string.h>
#include <ansii.h>
#include <printf.h>

void cmd_unknown(const char *cmd, long cmd_len) {
    (void)cmd; (void)cmd_len;

    printf("%s%s:%s Unknown Command\n", cmd, LIGHT_GRAY_FG, RESET);
}