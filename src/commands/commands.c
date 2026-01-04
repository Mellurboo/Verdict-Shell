#include <commands/commands.h>

struct command commands[] = {
    { "exit", cmd_exit },
    { "clear", cmd_clear },
    { "echo", cmd_echo },
    { "spawn", cmd_spawn },
};

const long COMMAND_COUNT = sizeof(commands)/sizeof(commands[0]);