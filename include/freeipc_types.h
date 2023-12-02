#ifndef __FREEIPC_TYPES_H__
#define __FREEIPC_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

struct ipc_message;
struct ipc_node;
struct ipc_manager;

typedef void (*ipc_node_service_func_t)(struct ipc_manager *self, struct ipc_node *node, struct ipc_message *msg);

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_TYPES_H__ */