#include <syscalls.h>
#include <libc/printf.h>
#include <ansii.h>

void cmd_spawn(const char *path, long args_len){
    (void)args_len;
    
    int pid = syscall_spawn(path);
    if (pid < 0){
        printf(LOG_ERROR "Kernel Attempted to start Program but got error code: %d", pid);
        return;
    }

    syscall_waitpid(pid);
    return;
}