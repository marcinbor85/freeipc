#include "common.h"

#include <stdio.h>

struct ipc_node g_consumer_node;
struct ipc_node g_producer_node;

struct ipc_manager g_ipc;

static void consumer_node_message_hook(struct ipc_manager *ipc, struct ipc_node *node, struct ipc_message *msg);
static void producer_node_message_hook(struct ipc_manager *ipc, struct ipc_node *node, struct ipc_message *msg);
static void producer_node_idle_hook(struct ipc_manager *ipc, struct ipc_node *node);

const struct ipc_node_descriptor g_consumer_node_desc = {
        .id = CONSUMER_NODE_ID,
        .message_hook = consumer_node_message_hook,
};

const struct ipc_node_descriptor g_producer_node_desc = {
        .id = PRODUCER_NODE_ID,
        .message_hook = producer_node_message_hook,
        .idle_hook = producer_node_idle_hook,
};

static void consumer_node_message_hook(struct ipc_manager *ipc, struct ipc_node *node, struct ipc_message *msg)
{
        static int request_cntr = 0;

        switch (msg->type) {
        case IPC_MESSAGE_TYPE_NOTIFY: {
                switch (msg->notify.value) {
                case NOTIFY_VALUE_PING:
                        printf("NOTIFY: ping from <%u>\n", msg->header.source_node_id);
                        ipc_node_notify(ipc, node, msg->header.source_node_id, NOTIFY_VALUE_PONG, NULL);
                        break;
                default:
                        break;
                }
                break;
        }

        case IPC_MESSAGE_TYPE_REQUEST: {
                printf("request received from %d: payload = ", msg->header.source_node_id);
                for (size_t i = 0; i < msg->payload.size; i++) {
                        printf("%c", msg->payload.data[i]);
                }
                printf("\n");

                request_cntr++;
                if (request_cntr % 5 != 0) {
                        printf("send response\n");
                        ipc_node_response(ipc, node, msg->header.id, NULL, 0);
                } else {
                        printf("no response\n");
                }
                
                break;
        }
        default:
                break;
        }
}

static void producer_node_message_hook(struct ipc_manager *ipc, struct ipc_node *node, struct ipc_message *msg)
{
        switch (msg->type) {
        case IPC_MESSAGE_TYPE_NOTIFY: {
                switch (msg->notify.value) {
                case NOTIFY_VALUE_PONG:
                        printf("NOTIFY: pong from <%u>\n", msg->header.source_node_id);
                        break;
                default:
                        break;
                }
                break;
        }
        case IPC_MESSAGE_TYPE_RESPONSE: {
                printf("response received\n");
                break;
        }
        case IPC_MESSAGE_TYPE_TIMEOUT: {
                printf("timeout received\n");
                break;
        }
        default:
                break;
        }
}

static void producer_node_idle_hook(struct ipc_manager *ipc, struct ipc_node *node)
{
        static uint32_t last_notify_ts = 0;
        static uint32_t last_request_ts = 0;

        uint32_t now = ipc_get_time(ipc);

        if (now - last_notify_ts > 1000) {
                last_notify_ts = now;
                ipc_node_notify(ipc, node, CONSUMER_NODE_ID, NOTIFY_VALUE_PING, NULL);
        }
        if (last_request_ts == 0) {
                last_request_ts = now;
        }
        if (now - last_request_ts > 3000) {
                last_request_ts = now;
                printf("send request\n");
                ipc_node_request(ipc, node, CONSUMER_NODE_ID, (uint8_t*)"abc", 3, 100);
        }
}
