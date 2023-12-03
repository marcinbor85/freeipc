#include "freeipc.h"
#include "freeipc_internal.h"

struct ipc_message* ipc_node_request(struct ipc_manager *self, struct ipc_node *node, uint32_t dest_node_id, uint8_t *payload, size_t payload_size, uint32_t timeout)
{
        struct ipc_message *msg = ipc_hal_malloc(self, sizeof(struct ipc_message));
        // TODO: check for NULL

        msg->id = ipc_utils_generate_message_id(self);
        msg->source_node_id = node->id;
        msg->dest_node_id = dest_node_id;
        msg->create_timestamp = ipc_get_time(self);

        msg->type = IPC_MESSAGE_TYPE_REQUEST;
        msg->request.timeout_value = timeout;
        msg->request.payload_size = payload_size;
        msg->request.payload = payload;

        bool success = ipc_hal_fifo_put_item(self, self->fifo, msg);
        if (success == false) {
                // TODO: handle error
                return NULL;
        }

        return msg;
}
