#include <string.h>
#include <stdarg.h>
#include <syscalls.h>
#include <write.h>

static void putc(char c) {
    _write(1, &c, 1);
}

static void putsn(const char *s, long n) {
    _write(1, s, n);
}

static void print_uint(unsigned long v, int base) {
    char buf[32];
    int i = 0;

    if (v == 0) {
        putc('0');
        return;
    }

    while (v) {
        unsigned d = v % base;
        buf[i++] = (d < 10) ? ('0' + d) : ('a' + d - 10);
        v /= base;
    }

    while (i--) putc(buf[i]);
}

static void print_int(long v) {
    if (v < 0) {
        putc('-');
        v = -v;
    }
    print_uint((unsigned long)v, 10);
}

int printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            putc(*fmt);
            continue;
        }

        fmt++;
        switch (*fmt) {
            case 's': {
                const char *s = va_arg(ap, const char *);
                if (s) putsn(s, strlen(s));
                else putsn("(null)", 6);
                break;
            }
            case 'd':
                print_int(va_arg(ap, int));
                break;
            case 'u':
                print_uint(va_arg(ap, unsigned), 10);
                break;
            case 'x':
                print_uint(va_arg(ap, unsigned), 16);
                break;
            case 'c':
                putc((char)va_arg(ap, int));
                break;
            case '%':
                putc('%');
                break;
            default:
                putc('%');
                putc(*fmt);
                break;
        }
    }

    va_end(ap);
    return 0;
}

