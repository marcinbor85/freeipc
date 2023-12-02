#include "freeipc_hal.h"

#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include <sys/time.h>

static uint32_t ipc_hal_get_time(struct ipc_manager *self)
{
        struct timeval ts;
        gettimeofday(&ts, NULL);
        return (uint32_t)(ts.tv_sec * 1000UL) + (uint32_t)(ts.tv_usec / 1000UL);
}

static void* ipc_hal_malloc(struct ipc_manager *self, size_t size)
{
        return malloc(size);
}

static void ipc_hal_free(struct ipc_manager *self, void *ptr)
{
        free(ptr);
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

struct fifo_item {
        struct fifo_item *next;
        void *item;
};

struct fifo {
        struct fifo_item *first;
        struct fifo_item *last;
};

void* ipc_hal_fifo_create(struct ipc_manager *self)
{
        struct fifo *f = malloc(sizeof(struct fifo));
        f->first = NULL;
        f->last = NULL;

        return f;
}

void* ipc_hal_fifo_get_item(struct ipc_manager *self, void *fifo, uint32_t max_wait_time)
{
        struct fifo *f = fifo;
        
        struct fifo_item *next = NULL;
        void *item = NULL;

        if (f->first == NULL)
                return NULL;
        
        next = f->first;
        item = f->first->item;

        f->first = next->next;
        if (f->first == NULL)
            f->last = NULL;

        free(next);

        return item;
}

void ipc_hal_fifo_put_item(struct ipc_manager *self, void *fifo, void *item)
{
        struct fifo *f = fifo;

        struct fifo_item *new_item = malloc(sizeof(struct fifo_item));
        new_item->item = item;
        new_item->next = NULL;
        
        if (f->last != NULL) {
            f->last->next = new_item;
            f->last = new_item;
        } else {
            f->first = new_item;
            f->last = new_item;
        }
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

const struct ipc_hal_interface *g_ipc_hal_interface_linux_no_threads = &_interface;