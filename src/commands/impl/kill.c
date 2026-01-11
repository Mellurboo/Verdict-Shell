#include <tkill.h>
#include <printf.h>
#include <stdlib.h>

void cmd_kill(const char *args, long cmd_len){
    (void)cmd_len;
    
    _tkill(atoi(args));
}