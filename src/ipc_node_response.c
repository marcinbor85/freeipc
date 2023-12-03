#include "freeipc.h"
#include "freeipc_internal.h"

struct ipc_message* ipc_node_response(struct ipc_manager *self, struct ipc_node *node, struct ipc_message *request_msg, uint8_t *payload, size_t payload_size)
{
        struct ipc_message *msg = ipc_hal_malloc(self, sizeof(struct ipc_message));
        // TODO: check for NULL

        msg->id = request_msg->id;
        msg->source_node_id = node->id;
        msg->dest_node_id = request_msg->source_node_id;
        msg->create_timestamp = ipc_get_time(self);

        msg->type = IPC_MESSAGE_TYPE_RESPONSE;
        msg->response.payload_size = payload_size;
        msg->response.payload = payload;

        bool success = ipc_hal_fifo_put_item(self, self->fifo, msg);
        if (success == false) {
                // TODO: handle error
                return NULL;
        }

        return msg;
}
