#include "freeipc.h"
#include "freeipc_internal.h"

struct ipc_message* ipc_node_notify(struct ipc_manager *self, struct ipc_node *node, uint32_t dest_node_id, uint32_t value, void *args)
{
        struct ipc_message *msg = ipc_hal_malloc(self, sizeof(struct ipc_message));
        // TODO: check for NULL

        msg->header.id = ipc_utils_generate_message_id(self);
        msg->header.source_node_id = node->id;
        msg->header.dest_node_id = dest_node_id;
        msg->header.create_timestamp = ipc_get_time(self);
        msg->header.timeout = 0;

        msg->type = IPC_MESSAGE_TYPE_NOTIFY;
        msg->notify.value = value;
        msg->notify.args = args;

        bool success = ipc_hal_fifo_put_item(self, self->fifo, msg);
        if (success == false) {
                // TODO: handle error
                return NULL;
        }

        return msg;
}
