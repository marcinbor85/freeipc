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

struct ipc_node* ipc_utils_get_node_by_id(struct ipc_manager *self, uint32_t id);
uint32_t ipc_utils_generate_message_id(struct ipc_manager *self);
struct ipc_message* ipc_utils_get_nearest_active_message(struct ipc_manager *self, uint32_t now, uint32_t *timeout);
void ipc_utils_remove_message_from_list(struct ipc_manager *self, uint32_t msg_id, bool dispose_msg);

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_INTERNAL_H__ */
