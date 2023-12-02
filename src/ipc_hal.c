#include "freeipc_internal.h"

uint32_t ipc_hal_get_time(struct ipc_manager *self)
{
        return self->hal->get_time(self);
}

void* ipc_hal_malloc(struct ipc_manager *self, size_t size)
{
        return self->hal->malloc(self, size);
}

void ipc_hal_free(struct ipc_manager *self, void *ptr)
{
        self->hal->free(self, ptr);
}

void* ipc_hal_mutex_create(struct ipc_manager *self)
{
        return self->hal->mutex_create(self);
}

void ipc_hal_mutex_lock(struct ipc_manager *self, void *mutex)
{
        self->hal->mutex_lock(self, mutex);
}

void ipc_hal_mutex_unlock(struct ipc_manager *self, void *mutex)
{
        self->hal->mutex_unlock(self, mutex);
}

void* ipc_hal_fifo_create(struct ipc_manager *self)
{
        return self->hal->fifo_create(self);
}

bool ipc_hal_fifo_get_item(struct ipc_manager *self, void *fifo, void **item, uint32_t max_wait_time)
{
        return self->hal->fifo_get_item(self, fifo, item, max_wait_time);
}

bool ipc_hal_fifo_put_item(struct ipc_manager *self, void *fifo, void *item)
{
        return self->hal->fifo_put_item(self, fifo, item);
}
