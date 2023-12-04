#include "freeipc_hal.h"

#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/time.h>

#include <stdio.h>

static uint32_t ipc_hal_get_time(struct ipc_manager *self)
{
        struct timeval ts;
        gettimeofday(&ts, NULL);
        return (uint32_t)(ts.tv_sec * 1000UL) + (uint32_t)(ts.tv_usec / 1000UL);
}

static void* ipc_hal_malloc(struct ipc_manager *self, size_t size)
{
        void *ptr = malloc(size);
        // printf("> malloc, ptr = %p, size = %lu, \n", ptr, size);
        return ptr;
}

static void ipc_hal_free(struct ipc_manager *self, void *ptr)
{
        // printf("> free,   ptr = %p\n", ptr);
        free(ptr);
}

static void* ipc_hal_mutex_create(struct ipc_manager *self)
{
        // TODO
        return NULL;
}

static void ipc_hal_mutex_lock(struct ipc_manager *self, void *mutex)
{
        // TODO
        return;
}

static void ipc_hal_mutex_unlock(struct ipc_manager *self, void *mutex)
{
        // TODO
        return;
}

struct fifo_item {
        struct fifo_item *next;
        void *item;
};

struct fifo {
        int output_fd;
        int input_fd;
};

static void* ipc_hal_fifo_create(struct ipc_manager *self)
{
        struct fifo *f = malloc(sizeof(struct fifo));

        int fd[2];
        int retval = pipe(fd);
        (void)retval;
        // TODO: add error handling

        f->output_fd = fd[0];
        f->input_fd = fd[1];

        return f;
}

static bool ipc_hal_fifo_get_item(struct ipc_manager *self, void *fifo, void **item, uint32_t max_wait_time)
{
        struct fifo *f = fifo;
        void *read_item = NULL;

        int retval;
        fd_set rfds;
        struct timeval tv;

        FD_ZERO(&rfds);
        FD_SET(f->output_fd, &rfds);

        // TODO: handle INFINITE DELAY

        tv.tv_sec = max_wait_time / 1000UL;
        tv.tv_usec = (max_wait_time % 1000UL) * 1000;

        retval = select(f->output_fd + 1, &rfds, NULL, NULL, (max_wait_time != (uint32_t)-1) ? &tv : NULL);
        if (retval) {
                int len = read(f->output_fd, &read_item, sizeof(void*));
                (void)len;
                // TODO: add error handling
                *item = read_item;
                return true;
        } else {
                // TODO: add error handling
        }

        *item = read_item;
        return false;
}

static bool ipc_hal_fifo_put_item(struct ipc_manager *self, void *fifo, void *item)
{
        struct fifo *f = fifo;

        int len = write(f->input_fd, (void*)&item, sizeof(void*));
        (void)len;
        // TODO: add error handling

        return true;
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

const struct ipc_hal_interface *g_ipc_hal_interface_linux_threads = &_interface;
