#include <clear.h>

void cmd_clear(const char *args, long args_len) {
    (void)args; (void)args_len;
    _clear(1);
}