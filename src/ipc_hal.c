#include "freeipc_internal.h"

#define IPC_LOG_TAG             "hal"
#define IPC_LOG_TAG_LEVEL       IPC_LOG_LEVEL_DEBUG

#include "freeipc_log.h"
#include "freeipc_assert.h"

uint32_t ipc_hal_get_time(struct ipc_manager *self)
{
        IPC_ASSERT(self != NULL);
        return self->desc->hal->get_time(self);
}

void* ipc_hal_malloc(struct ipc_manager *self, size_t size)
{
        IPC_ASSERT(self != NULL);
        return self->desc->hal->malloc(self, size);
}

void ipc_hal_free(struct ipc_manager *self, void *ptr)
{
        IPC_ASSERT(self != NULL);
        self->desc->hal->free(self, ptr);
}

void* ipc_hal_mutex_create(struct ipc_manager *self)
{
        IPC_ASSERT(self != NULL);
        return self->desc->hal->mutex_create(self);
}

void ipc_hal_mutex_lock(struct ipc_manager *self, void *mutex)
{
        IPC_ASSERT(self != NULL);
        self->desc->hal->mutex_lock(self, mutex);
}

void ipc_hal_mutex_unlock(struct ipc_manager *self, void *mutex)
{
        IPC_ASSERT(self != NULL);
        self->desc->hal->mutex_unlock(self, mutex);
}

void* ipc_hal_fifo_create(struct ipc_manager *self)
{
        IPC_ASSERT(self != NULL);
        return self->desc->hal->fifo_create(self);
}

bool ipc_hal_fifo_get_item(struct ipc_manager *self, void *fifo, void **item, uint32_t max_wait_time)
{
        IPC_ASSERT(self != NULL);
        return self->desc->hal->fifo_get_item(self, fifo, item, max_wait_time);
}

bool ipc_hal_fifo_put_item(struct ipc_manager *self, void *fifo, void *item)
{
        IPC_ASSERT(self != NULL);
        return self->desc->hal->fifo_put_item(self, fifo, item);
}
