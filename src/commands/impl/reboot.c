#include <syscalls.h>

void cmd_reboot(const char *path, long args_len){
    (void)path; (void)args_len;
    syscall_reboot();
}