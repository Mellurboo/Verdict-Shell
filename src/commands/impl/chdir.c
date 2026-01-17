#include <stdio.h>
#include <syscalls/chdir.h>
#include <main.h>

int cmd_chdir(shell_cmd_t *cmd) {
    if (cmd->argc < 2) {
        printf("Usage: cd <path>\n");
        return -1;
    }

    if (_chdir(cmd->argv[1]) < 0) {
        printf("cd: failed to change directory to %s\n", cmd->argv[1]);
        return -1;
    }

    return 0;
}
