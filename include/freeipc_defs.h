#ifndef __FREEIPC_DEFS_H__
#define __FREEIPC_DEFS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IPC_LOG_LEVEL_DEBUG     0
#define IPC_LOG_LEVEL_INFO      1
#define IPC_LOG_LEVEL_WARNING   2
#define IPC_LOG_LEVEL_ERROR     3
#define IPC_LOG_LEVEL_OFF       255

#define IPC_TIME_WAIT_FOREVER           ((uint32_t)(-1))
#define IPC_TIME_NO_WAIT                ((uint32_t)0)

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_DEFS_H__ */
