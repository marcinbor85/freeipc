#include "freeipc.h"
#include "freeipc_internal.h"

void ipc_node_register(struct ipc_manager *self, struct ipc_node *node, const struct ipc_node_descriptor *desc, void *context)
{
        node->desc = desc;
        
        node->context = context;
        node->state = IPC_NODE_STATE_RUNNING;
        node->fifo = ipc_hal_fifo_create(self);

        node->next = self->nodes;
        self->nodes = node;
}
