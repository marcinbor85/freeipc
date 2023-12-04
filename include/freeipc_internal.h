#ifndef __FREEIPC_INTERNAL_H__
#define __FREEIPC_INTERNAL_H__

#include "freeipc.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t ipc_hal_get_time(struct ipc_manager *self);
void* ipc_hal_malloc(struct ipc_manager *self, size_t size);
void ipc_hal_free(struct ipc_manager *self, void *ptr);
void* ipc_hal_mutex_create(struct ipc_manager *self);
void ipc_hal_mutex_lock(struct ipc_manager *self, void *mutex);
void ipc_hal_mutex_unlock(struct ipc_manager *self, void *mutex);
void* ipc_hal_fifo_create(struct ipc_manager *self);
bool ipc_hal_fifo_get_item(struct ipc_manager *self, void *fifo, void **item, uint32_t max_wait_time);
bool ipc_hal_fifo_put_item(struct ipc_manager *self, void *fifo, void *item);

struct ipc_node* ipc_utils_get_node(struct ipc_manager *self, uint32_t id);
uint32_t ipc_utils_generate_message_id(struct ipc_manager *self);
struct ipc_pending_message* ipc_utils_get_nearest_pending_message(struct ipc_manager *self, uint32_t now, uint32_t *timeout);
struct ipc_pending_message* ipc_utils_get_pending_message(struct ipc_manager *self, uint32_t msg_id);
void ipc_utils_remove_pending_message(struct ipc_manager *self, uint32_t msg_id);
void ipc_utils_add_pending_message(struct ipc_manager *self, struct ipc_message_header *header);

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_INTERNAL_H__ */
