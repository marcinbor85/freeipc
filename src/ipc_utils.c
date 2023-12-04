#include "freeipc.h"
#include "freeipc_internal.h"

struct ipc_node* ipc_utils_get_node(struct ipc_manager *self, uint32_t id)
{
        struct ipc_node *node = self->nodes;

        while (node != NULL) {
                if (node->id == id)
                        return node;
                node = node->next;
        }

        return NULL;
}

uint32_t ipc_utils_generate_message_id(struct ipc_manager *self)
{
        uint32_t ret = self->message_id_cntr;
        self->message_id_cntr++;
        return ret;
}

uint32_t ipc_utils_get_remaining_time(struct ipc_manager *self, struct ipc_pending_message *msg, uint32_t now)
{
    uint32_t diff = now - msg->header.create_timestamp;
    uint32_t ret = (diff >= msg->header.timeout) ? 0 : msg->header.timeout - diff;
    return ret;
}

struct ipc_pending_message* ipc_utils_get_pending_message(struct ipc_manager *self, uint32_t msg_id)
{
        struct ipc_pending_message *pending_message = self->pending_messages;

        while (pending_message != NULL) {                
                if (pending_message->header.id == msg_id)
                        return pending_message;
                pending_message = pending_message->next;
        }

        return NULL;
}

void ipc_utils_remove_pending_message(struct ipc_manager *self, uint32_t msg_id)
{
        struct ipc_pending_message *pending_message = self->pending_messages;
        struct ipc_pending_message *prev_pending_message = NULL;

        while (pending_message != NULL) {
                if (pending_message->header.id == msg_id) {
                        if (prev_pending_message == NULL) {
                                self->pending_messages = pending_message->next;
                        } else {
                                prev_pending_message->next = pending_message->next;
                        }
                        ipc_hal_free(self, pending_message);
                        return;
                }

                prev_pending_message = pending_message;
                pending_message = pending_message->next;
        }
}

void ipc_utils_add_pending_message(struct ipc_manager *self, struct ipc_message_header *header, uint32_t now)
{
        struct ipc_pending_message *pending_message = ipc_hal_malloc(self, sizeof(struct ipc_pending_message));
        // TODO: check for NULL

        pending_message->header = *header;
        pending_message->next = NULL;

        struct ipc_pending_message *next_pending_message = self->pending_messages;
        struct ipc_pending_message *prev_pending_message = NULL;

        if (next_pending_message == NULL) {
                self->pending_messages = pending_message;
                return;
        }

        uint32_t new_msg_remaining_time = ipc_utils_get_remaining_time(self, pending_message, now);

        while (next_pending_message != NULL) {
                uint32_t next_msg_remaining_time = ipc_utils_get_remaining_time(self, next_pending_message, now);

                if (new_msg_remaining_time < next_msg_remaining_time) {
                        pending_message->next = next_pending_message;
                        if (prev_pending_message == NULL) {
                                self->pending_messages = pending_message;
                        } else {
                                prev_pending_message->next = pending_message;
                        }
                        break;
                } else {
                        if (next_pending_message->next == NULL) {
                                next_pending_message->next = pending_message;
                                break;
                        }
                }

                prev_pending_message = next_pending_message;
                next_pending_message = next_pending_message->next;
        }
}
