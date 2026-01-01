#include <syscalls.h>
#include <stdint.h>
#include <libc/string.h>
#include <commands/commands.h>
#include <ansii.h>
#include <libc/printf.h>

void shell_init(){
    char buffer[BUFFER_SIZE];
    long bytes;

    while (1) {
        printf("%sshell@%sbleed-kernel%s$ ", RGB_FG(212, 44, 44), GRAY_FG, RESET);

        bytes = 0;
        while ((bytes = syscall_read(0, buffer, sizeof(buffer)-1)) == 0){ } // maybe this syscall should be blocking, it would make sense, for now lets wait

        buffer[bytes] = '\0';
        if (bytes > 0 && buffer[bytes-1] == '\n') buffer[--bytes] = '\0';

        char *cmd_end = buffer;
        while (*cmd_end && *cmd_end != ' ') cmd_end++;
        long cmd_len = cmd_end - buffer;

        char *args = cmd_end;
        if (*args == ' ') args++, bytes -= (args - buffer);
        else bytes = 0;

        command_t func = 0;
        for (long i = 0; i < COMMAND_COUNT; i++) {
            if (strncmp_fs(buffer, commands[i].name, cmd_len) == 0 && commands[i].name[cmd_len] == '\0') {
                func = commands[i].func;
                break;
            }
        }

        if (func) {
            func(args, bytes);
        } else {
            cmd_unknown(buffer, cmd_len);
        }
    }
}

__attribute__((noreturn))
void _start(void) {
    printf("Welcome to %sBleed-Kernel%s\nRunning Userspace Shell:%sVerdict%s\nCheck us out at bleedkernel.com\n",
    RGB_FG(212, 44, 44), RESET, RGB_FG(212, 44, 44), RESET);

    shell_init();
    __builtin_unreachable();
}
