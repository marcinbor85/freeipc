#ifndef __FREEIPC_ASSERT_H__
#define __FREEIPC_ASSERT_H__

#include "freeipc_config.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: do not check FREEIPC_CONFIG_ASSERT if assert disabled

#ifndef FREEIPC_CONFIG_ASSERT
#error "Missing macro FREEIPC_CONFIG_ASSERT in configuration"
#endif

#define IPC_ASSERT(cond)  FREEIPC_CONFIG_ASSERT(self, cond)

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_ASSERT_H__ */
