#pragma once

typedef struct dirent {
    char name[256];
    int type;
} dirent_t;

long _getdents(const char *path, dirent_t *entries, long max_entries);