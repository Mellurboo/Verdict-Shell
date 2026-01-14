#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <commands/commands.h>
#include <ansii.h>
#include <stdio.h>
#include <syscalls/read.h>
#include <syscalls/spawn.h>
#include <syscalls/waitpid.h>
#include <syscalls/time.h>
#include <syscalls/yeild.h>

#define SHELL_BUFFER_SIZE 256

void shell_init() {
    char buffer[SHELL_BUFFER_SIZE];
    long length = 0;

    while (1) {
        char ch;
        long bytes = _read(3, &ch, 1);
        if (bytes == 0) {
            continue;
        }

        if (ch != '\n' && ch != '\b') {
            printf("%c", ch);
        }

        if (ch == '\b' && length > 0) {
            length--;
            printf("\b \b");
            continue;
        }

        if (ch != '\n' && ch != '\b' && length < SHELL_BUFFER_SIZE - 1) {
            buffer[length++] = ch;
            continue;
        }

        buffer[length] = '\0';
        printf("\n");

        if (length > 0) {
            char *cmd_end = buffer;
            while (*cmd_end && *cmd_end != ' ') cmd_end++;
            long cmd_len = cmd_end - buffer;
            char *args = cmd_end;
            if (*args == ' ') args++, length -= (args - buffer);
            else length = 0;

            int handled = 0;

            if (cmd_len >= 2 && buffer[0] == '.' && buffer[1] == '/') {
                int pid = _spawn(buffer + 2);
                handled = 1;
                _waitpid(pid);
            }

            if (!handled) {
                command_t func = 0;
                for (long i = 0; i < COMMAND_COUNT; i++) {
                    if (strncmp(buffer, commands[i].name, cmd_len) == 0 &&
                        commands[i].name[cmd_len] == '\0') {
                        func = commands[i].func;
                        break;
                    }
                }

                if (func) {
                    func(args, length);
                    handled = 1;
                }
            }

            if (!handled) {
                cmd_unknown(buffer, cmd_len);
            }
        }

        length = 0;
        printf("%sshell@%sbleed-kernel%s$ ", RGB_FG(212, 44, 44), GRAY_FG, RESET);
    }
}

__attribute__((noreturn))
int main() {
    printf(
        "Welcome to %sBleed-Kernel%s\n"
        "Running Userspace Shell:%sVerdict%s\n"
        "Check us out at bleedkernel.com\n",
        RGB_FG(212, 44, 44), RESET,
        RGB_FG(212, 44, 44), RESET
    );

    printf("%sshell@%sbleed-kernel%s$ ", RGB_FG(212, 44, 44), GRAY_FG, RESET);
    shell_init();
    __builtin_unreachable();
}
