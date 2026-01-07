#include <syscalls.h>

void cmd_shutdown(const char *path, long args_len){
    (void)path; (void)args_len;
    syscall_shutdown();
}