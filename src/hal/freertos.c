#include "freeipc_hal.h"

#include <string.h>
#include <stddef.h>
#include <stdlib.h>

static uint32_t ipc_hal_get_time(struct ipc_manager *self)
{

}

static void* ipc_hal_malloc(struct ipc_manager *self, size_t size)
{
        return pvPortMalloc(size);
}

static void ipc_hal_free(struct ipc_manager *self, void *ptr)
{
        xPortFree(ptr);
}

void* ipc_hal_mutex_create(struct ipc_manager *self)
{
        return NULL;
}

void ipc_hal_mutex_lock(struct ipc_manager *self, void *mutex)
{
        return;
}

void ipc_hal_mutex_unlock(struct ipc_manager *self, void *mutex)
{
        return;
}

void* ipc_hal_fifo_create(struct ipc_manager *self)
{

}

void* ipc_hal_fifo_get_item(struct ipc_manager *self, void *fifo, uint32_t max_wait_time)
{

}

void ipc_hal_fifo_put_item(struct ipc_manager *self, void *fifo, void *item)
{

}

static const struct ipc_hal_interface _interface = {
        .get_time = ipc_hal_get_time,
        .malloc = ipc_hal_malloc,
        .free = ipc_hal_free,

        .mutex_create = ipc_hal_mutex_create,
        .mutex_lock = ipc_hal_mutex_lock,
        .mutex_unlock = ipc_hal_mutex_unlock,

        .fifo_create = ipc_hal_fifo_create,
        .fifo_get_item = ipc_hal_fifo_get_item,
        .fifo_put_item = ipc_hal_fifo_put_item,
};

const struct ipc_hal_interface *g_ipc_hal_interface_freertos = &_interface;
