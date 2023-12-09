#include "freeipc.h"
#include "freeipc_internal.h"

#define IPC_LOG_TAG             "service"
#define IPC_LOG_TAG_LEVEL       IPC_LOG_LEVEL_DEBUG

#include "freeipc_log.h"
#include "freeipc_assert.h"

void ipc_service(struct ipc_manager *self, uint32_t max_wait_time)
{
        struct ipc_message *msg = NULL;

        uint32_t now = 0;
        uint32_t timeout = 0;
        uint32_t wait_time = max_wait_time;

        struct ipc_pending_message *pending_message = self->pending_messages;

        if (pending_message != NULL) {
                now = ipc_get_time(self);
                timeout = ipc_utils_get_remaining_time(self, pending_message, now);
                if (timeout < wait_time) {
                        wait_time = timeout;
                }
        }

        bool success = ipc_hal_fifo_get_item(self, self->fifo, (void**)&msg, wait_time);
        if (success == false) {
                pending_message = self->pending_messages;
                if (pending_message != NULL) {
                        now = ipc_get_time(self);
                        timeout = ipc_utils_get_remaining_time(self, pending_message, now);

                        if (timeout == 0) {
                                msg = ipc_hal_malloc(self, sizeof(struct ipc_message));
                                IPC_ASSERT(msg != NULL);

                                msg->header.id = pending_message->header.id;
                                msg->header.source_node_id = pending_message->header.dest_node_id;
                                msg->header.dest_node_id = pending_message->header.source_node_id;;
                                msg->header.create_timestamp = ipc_get_time(self);
                                msg->header.timeout = 0;

                                msg->type = IPC_MESSAGE_TYPE_TIMEOUT;
                        }
                }
        }

        if (msg == NULL)
                return;

        struct ipc_node *src_node = ipc_utils_get_node(self, msg->header.source_node_id);
        if (src_node == NULL) {
                IPC_LOG_E("Source node doesn't exist");
                return;
        }

        struct ipc_node *dest_node = ipc_utils_get_node(self, msg->header.dest_node_id);
        if (dest_node == NULL) {
                IPC_LOG_E("Destination node doesn't exist");
                return;
        }

        switch (msg->type) {
        case IPC_MESSAGE_TYPE_NOTIFY: {
                IPC_LOG_I("Notify from <%s> to <%s>, value=%u", src_node->desc->name, dest_node->desc->name, msg->notify.value);
                break;
        }
        case IPC_MESSAGE_TYPE_REQUEST: {
                IPC_LOG_I("Request from <%s> to <%s>, msg_id=%u, type=%u", src_node->desc->name, dest_node->desc->name, msg->header.id, msg->payload.type);
                now = ipc_get_time(self);
                ipc_utils_add_pending_message(self, &msg->header, now);
                break;
        }
        case IPC_MESSAGE_TYPE_TIMEOUT: {
                IPC_LOG_W("Timeout from <%s> to <%s>, msg_id=%u", src_node->desc->name, dest_node->desc->name, msg->header.id);
                ipc_utils_remove_pending_message(self, msg->header.id);
                break;
        }
        case IPC_MESSAGE_TYPE_RESPONSE: {
                IPC_LOG_I("Response from <%s> to <%s>, msg_id=%u, type=%u", src_node->desc->name, dest_node->desc->name, msg->header.id, msg->payload.type);
                ipc_utils_remove_pending_message(self, msg->header.id);
                break;
        }
        default:
                break;
        }

        success = ipc_hal_fifo_put_item(self, dest_node->fifo, msg);
        if (success == false) {
                IPC_LOG_E("Cannot put item to fifo");
                return;
        }
}
