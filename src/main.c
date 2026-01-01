#include <syscalls.h>
#include <stdint.h>
#include <libc/string.h>
#include <commands/commands.h>
#include <ansii.h>

void shell_init(){
    char buffer[BUFFER_SIZE];
    long bytes;

    while (1) {
        syscall_write(1, RGB_FG(212, 44, 44), strlen(RGB_FG(212, 44, 44)));
        syscall_write(1, "shell@", strlen("shell@"));
        syscall_write(1, GRAY_FG, strlen(GRAY_FG));
        syscall_write(1, "bleed-kernel", strlen("bleed-kernel"));
        syscall_write(1, RGB_FG(255, 255, 255), strlen(RGB_FG(255, 255, 255)));
        syscall_write(1, "$ ", strlen("$ "));

        bytes = 0;
        while ((bytes = syscall_read(0, buffer, sizeof(buffer)-1)) == 0) {
            // yield here
        }

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
    syscall_write(1, "Welcome to ", strlen("Welcome to "));
    syscall_write(1, RGB_FG(212, 44, 44), strlen(RGB_FG(212, 44, 44)));
    syscall_write(1, "Bleed-Kernel\n", strlen("Bleed-Kernel!\n"));
    syscall_write(1, RESET, strlen(RESET));
    syscall_write(1, "Running Userspace Shell: ", strlen("Running Userspace Shell: "));
    syscall_write(1, RGB_FG(212, 44, 44), strlen(RGB_FG(212, 44, 44)));
    syscall_write(1, "Verdict\n", strlen("Verdict\n"));
    syscall_write(1, RESET, strlen(RESET));
    syscall_write(1, "Check us out at bleedkernel.com\n", strlen("Check us out at bleedkernel.com\n"));

    shell_init();
    __builtin_unreachable();
}
