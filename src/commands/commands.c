#include <commands/commands.h>

struct command commands[] = {
    { "exit", cmd_exit },
    { "clear", cmd_clear },
    { "echo", cmd_echo },
};

const long COMMAND_COUNT = sizeof(commands)/sizeof(commands[0]);