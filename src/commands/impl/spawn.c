#include <ansii.h>
#include <stdio.h>
#include <syscalls/spawn.h>
#include <syscalls/waitpid.h>
#include <commands/commands.h>

int cmd_spawn(shell_cmd_t *cmd){
    (void)cmd;
    
    int pid = _spawn(cmd->argv[2]);
    if (pid < 0){
        printf(LOG_ERROR "Kernel Attempted to start Program but got error code: %d\n", pid);
        return pid;
    }
    return 0;
}