#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>

#include "freeipc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PRODUCER_NODE_ID        1
#define CONSUMER_NODE_ID        2

#define NOTIFY_VALUE_PING       0x1001
#define NOTIFY_VALUE_PONG       0x1002

extern struct ipc_node g_consumer_node;
extern struct ipc_node g_producer_node;

extern const struct ipc_node_descriptor g_consumer_node_desc;
extern const struct ipc_node_descriptor g_producer_node_desc;

extern struct ipc_manager g_ipc;

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_H__ */
