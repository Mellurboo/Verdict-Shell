#include <syscalls/reboot.h>
#include <commands/commands.h>

int cmd_reboot(shell_cmd_t *cmd){
    (void)cmd;
    _reboot();
    return 0;
}