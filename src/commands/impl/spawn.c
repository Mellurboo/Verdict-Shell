#include <syscalls.h>

void cmd_spawn(const char *path, long args_len){
    (void)args_len;

    syscall_spawn(path);
    return;
}