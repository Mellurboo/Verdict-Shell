#include <syscalls/shutdown.h>
#include <commands/commands.h>

int cmd_shutdown(shell_cmd_t *cmd){
    (void)cmd;
    _shutdown();
    return 0;
}