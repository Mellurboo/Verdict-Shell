#pragma once
#include <stdint.h>

#define BUFFER_SIZE 128

typedef void (*command_t)(const char *args, long args_len);

struct command {
    const char *name;
    command_t func;
};

extern struct command commands[];
extern const long COMMAND_COUNT;

// Command functions
void cmd_exit(const char *args, long args_len);
void cmd_clear(const char *args, long args_len);
void cmd_echo(const char *args, long args_len);
void cmd_unknown(const char *args, long args_len);
void cmd_spawn(const char *path, long args_len);
void cmd_shutdown(const char *path, long args_len);
void cmd_reboot(const char *path, long args_len);
