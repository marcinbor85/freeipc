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
void* ipc_hal_fifo_get_item(struct ipc_manager *self, void *fifo, uint32_t max_wait_time);
void ipc_hal_fifo_put_item(struct ipc_manager *self, void *fifo, void *item);

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_INTERNAL_H__ */
