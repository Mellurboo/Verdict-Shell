#include <ansii.h>
#include <printf.h>
#include <spawn.h>
#include <waitpid.h>

void cmd_spawn(const char *path, long args_len){
    (void)args_len;
    
    int pid = _spawn(path);
    if (pid < 0){
        printf(LOG_ERROR "Kernel Attempted to start Program but got error code: %d", pid);
        return;
    }

    _waitpid(pid);
    return;
}