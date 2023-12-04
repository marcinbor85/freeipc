#ifndef __FREEIPC_H__
#define __FREEIPC_H__

#include "freeipc_structs.h"
#include "freeipc_types.h"
#include "freeipc_enums.h"
#include "freeipc_hal.h"
#include "freeipc_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

void ipc_init(struct ipc_manager *self, const struct ipc_hal_interface *hal, void *context);
void ipc_service(struct ipc_manager *self, uint32_t max_wait_time);

uint32_t ipc_get_time(struct ipc_manager *self);

void ipc_node_register(struct ipc_manager *self, struct ipc_node *node, const struct ipc_node_descriptor *desc, void *context);
void ipc_node_service(struct ipc_manager *self, struct ipc_node *node, uint32_t max_wait_time);

struct ipc_message* ipc_node_control(struct ipc_manager *self, struct ipc_node *node, uint32_t dest_node_id, ipc_control_cmd_t cmd);
struct ipc_message* ipc_node_notify(struct ipc_manager *self, struct ipc_node *node, uint32_t dest_node_id, uint32_t value, void *args);
struct ipc_message* ipc_node_request(struct ipc_manager *self, struct ipc_node *node, uint32_t dest_node_id, uint32_t type, uint8_t *payload, size_t payload_size, uint32_t timeout);
struct ipc_message* ipc_node_response(struct ipc_manager *self, struct ipc_node *node, uint32_t msg_id, uint32_t type, uint8_t *payload, size_t payload_size);

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_H__ */
