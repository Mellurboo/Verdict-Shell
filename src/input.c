#include <syscalls/read.h>
#include <stdio.h>
#include <main.h>

int shell_read_line(char *buf, size_t max) {
    size_t len = 0;

    while (len + 1 < max) {
        char c;
        if (_read(1, &c, 1) <= 0)
            continue;

        if (c == '\n') {
            buf[len] = 0;
            return len;
        }

        if (c == '\b') {
            if (len > 0) {
                len--;
                printf("\b \b");
            }
            continue;
        }

        buf[len++] = c;
    }

    buf[len] = 0;
    return len;
}
