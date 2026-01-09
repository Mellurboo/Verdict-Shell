#include <reboot.h>
void cmd_reboot(const char *path, long args_len){
    (void)path; (void)args_len;
    _reboot();
}