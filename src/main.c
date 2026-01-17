#include <stdio.h>
#include <string.h>
#include <main.h>
#include <ansii.h>
#include <syscalls/getcwd.h>

void prompt(void) {
    char cwd[4096];     // hardcoded pathmax lol add it to libc later
    if (!_getcwd(cwd, sizeof(cwd))) strcpy(cwd, "?");
    printf("["RGB_FG(212, 44, 44) "shell" GRAY_FG "@bleed-kernel" RGB_FG(212, 44, 44)"%s" RESET"]# ", cwd);
}

int main(void) {
    char line[SHELL_MAX_LINE];
    shell_cmd_t cmd;

    printf("Welcome to " RGB_FG(212, 44, 44) "The Bleed Kernel" RESET " by Mellurboo\n");

    if (path_init() < 0) {
        printf(LOG_WARN "failed to load PATH\n");
    }

    for (;;) {
        prompt();

        if (shell_read_line(line, sizeof(line)) <= 0)
            continue;

        if (shell_parse(line, &cmd) < 0)
            continue;

        shell_execute(&cmd);
    }
}