#pragma once
#include <main.h>

typedef int (*builtin_fn)(shell_cmd_t *);

typedef struct {
    const char *name;
    builtin_fn fn;
} builtin_t;

int builtin_dispatch(shell_cmd_t *cmd);
