#include "freeipc.h"
#include "freeipc_internal.h"

#define IPC_LOG_TAG             "init"
#define IPC_LOG_TAG_LEVEL       IPC_LOG_LEVEL_DEBUG

#include "freeipc_log.h"
#include "freeipc_assert.h"

void ipc_init(struct ipc_manager *self, const struct ipc_descriptor *desc, void *context)
{
        IPC_ASSERT(self != NULL);
        IPC_ASSERT(desc != NULL);

        self->nodes = NULL;
        self->desc = desc;
        self->context = context;
        self->pending_messages = NULL;
        self->message_id_cntr = 0;

        self->fifo = ipc_hal_fifo_create(self);
        // TODO: check for NULL
        self->mutex = ipc_hal_mutex_create(self);
        // TODO: check for NULL
}
