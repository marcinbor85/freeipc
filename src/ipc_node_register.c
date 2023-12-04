#include "freeipc.h"
#include "freeipc_internal.h"

void ipc_node_register(struct ipc_manager *self, struct ipc_node *node, uint32_t node_id, ipc_node_service_func_t func, void *context)
{
        node->id = node_id;
        node->service_func = func;
        node->context = context;
        node->state = IPC_NODE_STATE_RUNNING;
        node->fifo = ipc_hal_fifo_create(self);

        node->next = self->nodes;
        self->nodes = node;
}
