#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>

#include "freeipc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PRODUCER_NODE_ID        1
#define CONSUMER_NODE_ID        2

#define NOTIFY_VALUE_PING       1001
#define NOTIFY_VALUE_PONG       1002

#define REQUEST_TYPE_WRITE              1
#define REQUEST_TYPE_WRITE_ACK          101
#define REQUEST_TYPE_READ               2
#define REQUEST_TYPE_READ_ACK           102

extern struct ipc_node g_consumer_node;
extern struct ipc_node g_producer_node;

extern const struct ipc_node_descriptor g_consumer_node_desc;
extern const struct ipc_node_descriptor g_producer_node_desc;

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_H__ */
