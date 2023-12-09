#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/time.h>

#include "freeipc.h"

static const struct { char *name; char *color; } gLevelsDescriptor[] = {
        {"DEBUG", "\x1B[0m"},
        {"INFO", "\x1B[32m"},
        {"WARN", "\x1B[33m"},
        {"ERROR", "\x1B[31m"},
};

void print_log(void *self, int level, const char *tag, const char *filename, int line, const char *format, ...)
{
        struct ipc_manager *ipc = (struct ipc_manager*)self;

        va_list args;
        va_start(args, format);

        struct timeval tv;
        gettimeofday(&tv, NULL);
        unsigned _timestamp = (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
        
        fprintf(stdout, "%s%010u [%-5s|%-4s|%-8s|%4d] ", gLevelsDescriptor[level].color, (unsigned)_timestamp, gLevelsDescriptor[level].name, ipc->desc->name, tag, line);
        vfprintf(stdout, format, args);
        fprintf(stdout, "\x1B[0m\n");

        va_end(args);
}
