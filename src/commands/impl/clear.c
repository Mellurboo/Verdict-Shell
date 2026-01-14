#include <stdio.h>

void cmd_clear(const char *args, long args_len) {
    (void)args; (void)args_len;
    printf("\x1b[Jm");
}