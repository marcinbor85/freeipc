#include "freeipc.h"
#include "freeipc_internal.h"

#include <stdio.h>

void ipc_service(struct ipc_manager *self, uint32_t max_wait_time)
{
        struct ipc_message *msg = NULL;

        uint32_t now = ipc_get_time(self);
        uint32_t timeout = 0;
        struct ipc_pending_message *pending_message = ipc_utils_get_nearest_pending_message(self, now, &timeout);

        uint32_t wait_time = ((pending_message != NULL) && (timeout < max_wait_time)) ? timeout : max_wait_time;        

        if (pending_message != NULL) {
                printf("pending_message, timeout = %u\n", timeout);
        }
        bool success = ipc_hal_fifo_get_item(self, self->fifo, (void**)&msg, wait_time);
        if (success == false) {
                pending_message = ipc_utils_get_nearest_pending_message(self, now, &timeout);
                if ((pending_message != NULL) && (timeout == 0)) {

                        msg = ipc_hal_malloc(self, sizeof(struct ipc_message));
                        // TODO: check for NULL

                        msg->header.id = pending_message->header.id;
                        msg->header.source_node_id = pending_message->header.dest_node_id;
                        msg->header.dest_node_id = pending_message->header.source_node_id;;
                        msg->header.create_timestamp = ipc_get_time(self);
                        msg->header.timeout = 0;

                        msg->type = IPC_MESSAGE_TYPE_TIMEOUT;

                        // remove message from list
                        ipc_utils_remove_pending_message(self, pending_message->header.id);
                }
        }

        if (msg == NULL)
                return;

        struct ipc_node *node = ipc_utils_get_node(self, msg->header.dest_node_id);
        if (node == NULL) {
                // TODO: handle error
                return;
        }

        switch (msg->type) {
        case IPC_MESSAGE_TYPE_REQUEST: {
                ipc_utils_add_pending_message(self, &msg->header);
                break;
        }
        case IPC_MESSAGE_TYPE_RESPONSE: {
                // remove message from list
                ipc_utils_remove_pending_message(self, msg->header.id);
                break;
        }
        default:
                break;
        }

        success = ipc_hal_fifo_put_item(self, node->fifo, msg);
        if (success == false) {
                // TODO: handle error
                return;
        }
}
