#include "freeipc.h"
#include "freeipc_internal.h"

void ipc_node_service(struct ipc_manager *self, struct ipc_node *node, uint32_t max_wait_time)
{
        struct ipc_message *msg = NULL;

        uint32_t wait_time = max_wait_time;
        // TODO: calculate wait_time based on max_wait_time and active messages

        ipc_hal_fifo_get_item(self, node->fifo, (void**)&msg, wait_time);
        
        node->service_func(self, node, msg);

        // TODO: if request, then do not free message, it is still active until response

        if (msg != NULL) {
                if (msg->type != IPC_MESSAGE_TYPE_REQUEST) {
                        ipc_hal_free(self, msg);
                }
        }
}
