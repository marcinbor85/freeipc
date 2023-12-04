#include "freeipc.h"
#include "freeipc_internal.h"

#include <string.h>

struct ipc_message* ipc_node_request(struct ipc_manager *self, struct ipc_node *node, uint32_t dest_node_id, uint8_t *payload, size_t payload_size, uint32_t timeout)
{
        struct ipc_message *msg = ipc_hal_malloc(self, sizeof(struct ipc_message) + payload_size);
        // TODO: check for NULL

        msg->header.id = ipc_utils_generate_message_id(self);
        msg->header.source_node_id = node->id;
        msg->header.dest_node_id = dest_node_id;
        msg->header.create_timestamp = ipc_get_time(self);
        msg->header.timeout = timeout;

        msg->type = IPC_MESSAGE_TYPE_REQUEST;
        
        msg->payload.size = payload_size;
        memcpy(msg->payload.data, payload, payload_size);

        bool success = ipc_hal_fifo_put_item(self, self->fifo, msg);
        if (success == false) {
                // TODO: handle error
                return NULL;
        }

        return msg;
}
