#include "freeipc.h"
#include "freeipc_internal.h"

void ipc_node_register(struct ipc_manager *self, struct ipc_node *node, uint32_t node_id, ipc_node_service_func_t func, void *context)
{
        node->id = node_id;
        node->service_func = func;
        node->context = context;
        node->state = IPC_NODE_STATE_RUNNING;
        node->fifo = ipc_hal_fifo_create(self);

        struct ipc_node_list *new_node = ipc_hal_malloc(self, sizeof(struct ipc_node_list));
        // TODO: check for NULL

        new_node->node = node;
        new_node->next = (self->nodes != NULL) ? self->nodes : NULL;

        self->nodes = new_node;        
}
