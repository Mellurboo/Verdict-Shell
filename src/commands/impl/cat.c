#include <stdio.h>
#include <syscalls/open.h>
#include <syscalls/close.h>
#include <syscalls/read.h>
#include <syscalls/write.h>
#include <stdlib.h>
#include <string.h>
#include <commands/commands.h>

int cmd_cat(shell_cmd_t *cmd) {
    if (cmd->argc < 2) {
        printf("Bad Command Usage: cat <file>\n");
        return -1;
    }

    const char *filename = cmd->argv[1];
    char buf[256];

    int fd = _open(filename, O_RDONLY);
    if (fd < 0) {
        printf("cat: cannot open %s\n", filename);
        return -2;
    }

    for (;;) {
        long r = _read(fd, buf, sizeof(buf));
        if (r == 0)
            break;
        if (r < 0) {
            printf("cat: read error (%ld)\n", r);
            break;
        }
        _write(1, buf, r);
    }

    _close(fd);
    return 0;
}