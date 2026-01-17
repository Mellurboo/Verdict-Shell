#include <string.h>
#include <main.h>

int shell_parse(char *line, shell_cmd_t *cmd) {
    cmd->argc = 0;

    char *p = line;
    while (*p) {
        while (*p == ' ')
            p++;

        if (!*p)
            break;

        if (cmd->argc >= SHELL_MAX_ARGS)
            break;

        cmd->argv[cmd->argc++] = p;

        while (*p && *p != ' ')
            p++;

        if (*p)
            *p++ = 0;
    }

    cmd->argv[cmd->argc] = 0;
    return cmd->argc > 0 ? 0 : -1;
}
