#include "freeipc.h"
#include "freeipc_internal.h"

void ipc_init(struct ipc_manager *self, const struct ipc_hal_interface *hal, void *context)
{
        self->nodes = NULL;
        self->hal = hal;
        self->context = context;
        self->pending_messages = NULL;
        self->message_id_cntr = 0;

        self->fifo = ipc_hal_fifo_create(self);
        // TODO: check for NULL
        self->mutex = ipc_hal_mutex_create(self);
        // TODO: check for NULL
}
