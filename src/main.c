#include <stdint.h>
#include <string.h>
#include <commands/commands.h>
#include <ansii.h>
#include <printf.h>
#include <read.h>
#include <spawn.h>
#include <waitpid.h>

void shell_init(){
    char buffer[BUFFER_SIZE];
    long bytes;

    while (1) {
        bytes = 0;
        while ((bytes = _read(0, buffer, sizeof(buffer)-1)) == 0) { }

        buffer[bytes] = '\0';
        if (bytes > 0 && buffer[bytes-1] == '\n') buffer[--bytes] = '\0';

        char *cmd_end = buffer;
        while (*cmd_end && *cmd_end != ' ') cmd_end++;
        long cmd_len = cmd_end - buffer;

        char *args = cmd_end;
        if (*args == ' ') args++, bytes -= (args - buffer);
        else bytes = 0;

        int handled = 0;

        if (cmd_len >= 2 && buffer[0] == '.' && buffer[1] == '/') {
            int pid = _spawn(buffer + 2);
            _waitpid(pid);
            handled = 1;
        }

        if (!handled) {
            command_t func = 0;
            for (long i = 0; i < COMMAND_COUNT; i++) {
                if (strncmp_fs(buffer, commands[i].name, cmd_len) == 0 &&
                    commands[i].name[cmd_len] == '\0') {
                    func = commands[i].func;
                    break;
                }
            }

            if (func) {
                func(args, bytes);
                handled = 1;
            }
        }

        if (!handled) {
            cmd_unknown(buffer, cmd_len);
        }

        printf("%sshell@%sbleed-kernel%s$ ", RGB_FG(212, 44, 44), GRAY_FG, RESET);
    }

}

__attribute__((noreturn))
int main() {
    printf("Welcome to %sBleed-Kernel%s\nRunning Userspace Shell:%sVerdict%s\nCheck us out at bleedkernel.com\n",
    RGB_FG(212, 44, 44), RESET, RGB_FG(212, 44, 44), RESET);
    printf("%sshell@%sbleed-kernel%s$ ", RGB_FG(212, 44, 44), GRAY_FG, RESET);
    shell_init();
    __builtin_unreachable();
}
