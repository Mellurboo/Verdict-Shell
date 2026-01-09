#pragma once

enum {
    SYS_READ,
    SYS_WRITE,
    SYS_EXIT,
    SYS_CLEAR,
    SYS_YEILD,
    SYS_SPAWN,
    SYS_WAITPID,
    SYS_SHUTDOWN,
    SYS_REBOOT,
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
        : "a"(SYS_YEILD)
        : "rcx", "r11", "memory"
    );
    __builtin_unreachable();
}

static inline int syscall_spawn(const char *path) {
    int pid;
    asm volatile(
        "int $0x80"
        : "=a"(pid)
        : "a"(SYS_SPAWN), "D"(path)
        : "rcx", "r11", "memory"
    );
    return pid;
}

static inline long syscall_waitpid(long pid){
    long ret;
    asm volatile(
        "int $0x80"
        : "=a"(ret)
        : "a"(SYS_WAITPID), "D"(pid)
        : "memory"
    );

    return ret;
}

static inline void syscall_shutdown() {
    __asm__ volatile (
        "int $0x80"
        :
        : "a"(SYS_SHUTDOWN)
        : "rcx", "r11", "memory"
    );
    __builtin_unreachable();
}

static inline void syscall_reboot() {
    __asm__ volatile (
        "int $0x80"
        :
        : "a"(SYS_REBOOT)
        : "rcx", "r11", "memory"
    );
    __builtin_unreachable();
}