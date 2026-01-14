#include <ansii.h>
#include <stdio.h>
#include <syscalls/spawn.h>
#include <syscalls/waitpid.h>

void cmd_spawn(const char *path, long args_len){
    (void)args_len;
    
    int pid = _spawn(path);
    if (pid < 0){
        printf(LOG_ERROR "Kernel Attempted to start Program but got error code: %d", pid);
        return;
    }
    return;
}