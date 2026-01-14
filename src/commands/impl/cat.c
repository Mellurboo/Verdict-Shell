#include <stdio.h>
#include <syscalls/open.h>
#include <syscalls/close.h>
#include <syscalls/read.h>
#include <syscalls/write.h>
#include <stdlib.h>
#include <string.h>

void cmd_cat(const char *filename) {
    char buf[256];
    int fd = _open(filename, O_RDONLY);
    if (fd < 0) return;

    long total_read_count;
    long r;
    while ((r = _read(fd, buf, sizeof(buf))) > 0) {
        total_read_count += r;
        _write(1, buf, r);
    }

    if (total_read_count < 0) {
        printf("Failed to read file (error %ld)\n", r);
    }

    _close(fd);
}