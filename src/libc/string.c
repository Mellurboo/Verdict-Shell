#include <stddef.h>

int str_eq(const char *a, const char *b) {
    while (*a && *b) {
        if (*a++ != *b++) return 0;
    }
    return *a == *b;
}

int strncmp_fs(const char *a, const char *b, long n) {
    for (long i = 0; i < n; i++) {
        if (a[i] != b[i]) return (unsigned char)a[i] - (unsigned char)b[i];
        if (a[i] == '\0') return 0;
    }
    return 0;
}

size_t strlen(const char *string){
    if (string == NULL) return 0;

    size_t length = 0;
    while (*string != '\0'){
        length++;
        string++;
    }
    return length;
}