#include "freeipc.h"
#include "freeipc_internal.h"

#include <stdio.h>

void ipc_service(struct ipc_manager *self, uint32_t max_wait_time)
{
        struct ipc_message *msg = NULL;

        uint32_t now = ipc_get_time(self);
        uint32_t timeout = 0;
        struct ipc_message *nearest_msg = ipc_utils_get_nearest_active_message(self, now, &timeout);

        uint32_t wait_time = ((nearest_msg != NULL) && (timeout < max_wait_time)) ? timeout : max_wait_time;        

        bool success = ipc_hal_fifo_get_item(self, self->fifo, (void**)&msg, wait_time);
        if (success == false) {
                nearest_msg = ipc_utils_get_nearest_active_message(self, now, &timeout);
                if ((nearest_msg != NULL) && (timeout == 0)) {

                        msg = nearest_msg;
                        msg->type = IPC_MESSAGE_TYPE_REQUEST_TIMEOUT;
                        uint32_t tmp_node_id = msg->dest_node_id;
                        msg->dest_node_id = msg->source_node_id;
                        msg->source_node_id = tmp_node_id;

                        // remove message from list
                        ipc_utils_remove_message_from_list(self, msg->id, false);

                } else {
                        return;
                }
        }

        struct ipc_node *node = ipc_utils_get_node_by_id(self, msg->dest_node_id);
        if (node == NULL) {
                // TODO: handle error
                return;
        }

        switch (msg->type) {
        case IPC_MESSAGE_TYPE_REQUEST: {
                struct ipc_message_list *new_message = ipc_hal_malloc(self, sizeof(struct ipc_message_list));
                // TODO: check for NULL

                new_message->msg = msg;
                new_message->next = (self->active_messages != NULL) ? self->active_messages : NULL;

                self->active_messages = new_message;
                break;
        }
        case IPC_MESSAGE_TYPE_RESPONSE: {
                // remove message from list
                ipc_utils_remove_message_from_list(self, msg->id, true);
                break;
        }
        default:
                break;
        }

        // TODO: add support for requests

        success = ipc_hal_fifo_put_item(self, node->fifo, msg);
        if (success == false) {
                // TODO: handle error
                return;
        }
}
