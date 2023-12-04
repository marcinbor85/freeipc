#include "freeipc.h"
#include "freeipc_internal.h"

#include <string.h>

struct ipc_message* ipc_node_response(struct ipc_manager *self, struct ipc_node *node, uint32_t msg_id, uint32_t type, uint8_t *payload, size_t payload_size)
{
        struct ipc_pending_message *pending_message = ipc_utils_get_pending_message(self, msg_id);
        // TODO: check for NULL

        struct ipc_message *msg = ipc_hal_malloc(self, sizeof(struct ipc_message) + payload_size);
        // TODO: check for NULL


        msg->header.id = msg_id;
        msg->header.source_node_id = node->desc->id;
        msg->header.dest_node_id = pending_message->header.source_node_id;
        msg->header.create_timestamp = ipc_get_time(self);
        msg->header.timeout = 0;

        msg->type = IPC_MESSAGE_TYPE_RESPONSE;

        msg->payload.type = type;
        msg->payload.size = payload_size;
        memcpy(msg->payload.data, payload, payload_size);

        bool success = ipc_hal_fifo_put_item(self, self->fifo, msg);
        if (success == false) {
                // TODO: handle error
                return NULL;
        }

        return msg;
}
