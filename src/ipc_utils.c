#include "freeipc.h"
#include "freeipc_internal.h"

struct ipc_node* ipc_utils_get_node_by_id(struct ipc_manager *self, uint32_t id)
{
        struct ipc_node_list *list_item = self->nodes;

        while (list_item != NULL) {
                struct ipc_node *node = list_item->node;
                if (node->id == id)
                        return node;
                list_item = list_item->next;
        }

        return NULL;
}

uint32_t ipc_utils_generate_message_id(struct ipc_manager *self)
{
        uint32_t ret = self->message_id_cntr;
        self->message_id_cntr++;
        return ret;
}

struct ipc_message* ipc_utils_get_nearest_active_message(struct ipc_manager *self, uint32_t now, uint32_t *timeout)
{
        struct ipc_message* nearest_msg = NULL;
        struct ipc_message_list *list_item = self->active_messages;

        while (list_item != NULL) {
                struct ipc_message *msg = list_item->msg;
                
                if (msg->type == IPC_MESSAGE_TYPE_REQUEST) {
                        uint32_t diff = now - msg->create_timestamp;
                        uint32_t after = (diff >= msg->request.timeout_value) ? 0 : msg->request.timeout_value - diff;
                        if ((nearest_msg == NULL) || (after < *timeout)) {
                                *timeout = after;
                                nearest_msg = msg;
                        }
                }

                list_item = list_item->next;
        }

        return nearest_msg;
}

void ipc_utils_remove_message_from_list(struct ipc_manager *self, uint32_t msg_id, bool dispose_msg)
{
        struct ipc_message_list *list_item = self->active_messages;
        struct ipc_message_list *prev_list_item = NULL;

        while (list_item != NULL) {
                struct ipc_message *message = list_item->msg;

                if (message->id == msg_id) {
                        if (prev_list_item == NULL) {
                                self->active_messages = list_item->next;
                        } else {
                                prev_list_item->next = list_item->next;
                        }
                        ipc_hal_free(self, list_item);

                        if (dispose_msg) {
                                ipc_hal_free(self, message);
                        }
                        return;
                }

                prev_list_item = list_item;
                list_item = list_item->next;
        }
}
