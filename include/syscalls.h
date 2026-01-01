#pragma once

enum {
    SYS_READ,
    SYS_WRITE,
    SYS_EXIT,
    SYS_CLEAR,
    SYS_YIELD,
};

static inline long syscall_read(int fd, void *buf, unsigned long len) {
    long ret;
    __asm__ volatile (
        "int $0x80"
        : "=a"(ret)
        : "a"(SYS_READ),
          "D"(fd),
          "S"(buf),
          "d"(len)
        : "rcx", "r11", "memory"
    );
    return ret;
}

static inline long syscall_write(int fd, const void *buf, unsigned long len) {
    long ret;
    __asm__ volatile (
        "int $0x80"
        : "=a"(ret)
        : "a"(SYS_WRITE),
          "D"(fd),
          "S"(buf),
          "d"(len)
        : "rcx", "r11", "memory"
    );
    return ret;
}

static inline void syscall_exit(long c) {
    __asm__ volatile (
        "int $0x80"
        :
        : "a"(SYS_EXIT),
          "D"(c)
        : "rcx", "r11", "memory"
    );
    __builtin_unreachable();
}

static inline void syscall_clear(int fd) {
    __asm__ volatile (
        "int $0x80"
        :
        : "a"(SYS_CLEAR),
          "D"(fd)
        : "rcx", "r11", "memory"
    );
}

static inline void syscall_yield() {
    __asm__ volatile (
        "int $0x80"
        :
        : "a"(SYS_YIELD)
        : "rcx", "r11", "memory"
    );
    __builtin_unreachable();
}