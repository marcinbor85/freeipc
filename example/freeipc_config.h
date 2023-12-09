#ifndef __FREEIPC_CONFIG_H__
#define __FREEIPC_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define FREEIPC_CONFIG_LOG_LEVEL        0

extern void print_log(void *self, int level, const char *tag, const char *filename, int line, const char *format, ...);

#define FREEIPC_CONFIG_LOG(self, level, tag, format, ...) \
{ \
        print_log(self, level, tag, __FILE__, __LINE__, format, ## __VA_ARGS__); \
}

#define FREEIPC_CONFIG_ASSERT(self, cond) \
{ \
        if (!(cond)) { \
                fprintf(stderr, "\x1B[31mASSERT [%s] %s:%d\x1B[0m\n", self->desc->name, __FILE__, __LINE__); \
                exit(-1); \
        } \
}

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_CONFIG_H__ */
