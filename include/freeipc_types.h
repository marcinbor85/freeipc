#ifndef __FREEIPC_TYPES_H__
#define __FREEIPC_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

// TODO: add typedefs to node_id, message_id, etc...

struct ipc_message;
struct ipc_node;
struct ipc_manager;

typedef void (*ipc_node_message_hook_t)(struct ipc_manager *self, struct ipc_node *node, struct ipc_message *msg);
typedef void (*ipc_node_idle_hook_t)(struct ipc_manager *self, struct ipc_node *node);

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_TYPES_H__ */
