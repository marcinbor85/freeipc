#ifndef __FREEIPC_LOG_H__
#define __FREEIPC_LOG_H__

#include "freeipc_config.h"
#include "freeipc_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IPC_LOG_TAG_LEVEL
#error "Please define IPC_LOG_TAG_LEVEL to use logger"
#endif

#ifndef IPC_LOG_TAG
#error "Please define IPC_LOG_TAG to use logger"
#endif

#ifndef FREEIPC_CONFIG_LOG_LEVEL
#define FREEIPC_CONFIG_LOG_LEVEL IPC_LOG_LEVEL_OFF
#endif

// TODO: do not check FREEIPC_CONFIG_LOG if logger disabled

#ifndef FREEIPC_CONFIG_LOG
#error "Missing macro FREEIPC_CONFIG_LOG in configuration"
#endif

#if FREEIPC_CONFIG_LOG_LEVEL <= IPC_LOG_LEVEL_DEBUG
#if IPC_LOG_TAG_LEVEL <= IPC_LOG_LEVEL_DEBUG
#define IPC_LOG_D(...)  FREEIPC_CONFIG_LOG(self, IPC_LOG_LEVEL_DEBUG, IPC_LOG_TAG, __VA_ARGS__)
#else
#define IPC_LOG_D(...)
#endif
#else
#define IPC_LOG_D(...)
#endif

#if FREEIPC_CONFIG_LOG_LEVEL <= IPC_LOG_LEVEL_INFO
#if IPC_LOG_TAG_LEVEL <= IPC_LOG_LEVEL_INFO
#define IPC_LOG_I(...)  FREEIPC_CONFIG_LOG(self, IPC_LOG_LEVEL_INFO, IPC_LOG_TAG, __VA_ARGS__)
#else
#define IPC_LOG_I(...)
#endif
#else
#define IPC_LOG_I(...)
#endif

#if FREEIPC_CONFIG_LOG_LEVEL <= IPC_LOG_LEVEL_WARNING
#if IPC_LOG_TAG_LEVEL <= IPC_LOG_LEVEL_WARNING
#define IPC_LOG_W(...)  FREEIPC_CONFIG_LOG(self, IPC_LOG_LEVEL_WARNING, IPC_LOG_TAG, __VA_ARGS__)
#else
#define IPC_LOG_W(...)
#endif
#else
#define IPC_LOG_W(...)
#endif

#if FREEIPC_CONFIG_LOG_LEVEL <= IPC_LOG_LEVEL_ERROR
#if IPC_LOG_TAG_LEVEL <= IPC_LOG_LEVEL_ERROR
#define IPC_LOG_E(...)  FREEIPC_CONFIG_LOG(self, IPC_LOG_LEVEL_ERROR, IPC_LOG_TAG, __VA_ARGS__)
#else
#define IPC_LOG_E(...)
#endif
#else
#define IPC_LOG_E(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_LOG_H__ */
