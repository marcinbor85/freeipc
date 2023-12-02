#ifndef __FREEIPC_HAL_H__
#define __FREEIPC_HAL_H__

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ipc_manager;

struct ipc_hal_interface {
        uint32_t (*get_time)(struct ipc_manager *self);
        void* (*malloc)(struct ipc_manager *self, size_t size);
        void (*free)(struct ipc_manager *self, void *ptr);

        void* (*mutex_create)(struct ipc_manager *self);
        void (*mutex_lock)(struct ipc_manager *self, void *mutex);
        void (*mutex_unlock)(struct ipc_manager *self, void *mutex);

        void* (*fifo_create)(struct ipc_manager *self);
        void* (*fifo_get_item)(struct ipc_manager *self, void *fifo, uint32_t max_wait_time);
        void (*fifo_put_item)(struct ipc_manager *self, void *fifo, void *item);
};

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_HAL_H__ */
