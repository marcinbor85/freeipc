#include "freeipc.h"

void ipc_node_register(struct ipc_manager *self, struct ipc_node *node, uint32_t node_id, ipc_node_service_func_t func, void *context)
{
        node->service_func = func;
}
