#include "freeipc.h"
#include "freeipc_internal.h"

void ipc_node_service(struct ipc_manager *self, struct ipc_node *node, uint32_t max_wait_time)
{
        struct ipc_message *msg = NULL;

        uint32_t wait_time = max_wait_time;

        ipc_hal_fifo_get_item(self, node->fifo, (void**)&msg, wait_time);
        
        if (msg != NULL) {
                node->callback_func(self, node, msg);
                ipc_hal_free(self, msg);
        }
}
