#include "common.h"

#include <stdio.h>

struct ipc_node g_consumer_node;
struct ipc_node g_producer_node;

static void consumer_node_message_hook(struct ipc_manager *ipc, struct ipc_node *node, struct ipc_message *msg);
static void producer_node_message_hook(struct ipc_manager *ipc, struct ipc_node *node, struct ipc_message *msg);
static void producer_node_idle_hook(struct ipc_manager *ipc, struct ipc_node *node);

const struct ipc_node_descriptor g_consumer_node_desc = {
        .id = CONSUMER_NODE_ID,
        .name = "consumer",
        .message_hook = consumer_node_message_hook,
};

const struct ipc_node_descriptor g_producer_node_desc = {
        .id = PRODUCER_NODE_ID,
        .name = "producer",
        .message_hook = producer_node_message_hook,
        .idle_hook = producer_node_idle_hook,
};

static void consumer_node_message_hook(struct ipc_manager *ipc, struct ipc_node *node, struct ipc_message *msg)
{
        switch (msg->type) {
        case IPC_MESSAGE_TYPE_NOTIFY: {
                switch (msg->notify.value) {
                case NOTIFY_VALUE_PING:
                        printf("PING\n");
                        ipc_node_notify(ipc, node, msg->header.source_node_id, NOTIFY_VALUE_PONG, NULL);
                        break;
                default:
                        break;
                }
                break;
        }

        case IPC_MESSAGE_TYPE_REQUEST: {
                switch (msg->payload.type) {
                case REQUEST_TYPE_WRITE:
                        printf("WRITE [");
                        for (size_t i = 0; i < msg->payload.size; i++) {
                                printf("%c", msg->payload.data[i]);
                        }
                        printf("]\n");
                        ipc_node_response(ipc, node, msg->header.id, REQUEST_TYPE_WRITE_ACK, NULL, 0);
                        break;

                case REQUEST_TYPE_READ:
                        printf("READ [");
                        for (size_t i = 0; i < msg->payload.size; i++) {
                                printf("%c", msg->payload.data[i]);
                        }
                        printf("]\n");
                        if (msg->payload.size > 0) {
                                ipc_node_response(ipc, node, msg->header.id, REQUEST_TYPE_READ_ACK, (uint8_t*)"some_data", 9);
                        } else {
                                // in case of no response, timeout will be triggered automatically by ipc
                        }
                        break;
                
                default:
                        break;
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
                        printf("PONG\n");
                        break;
                default:
                        break;
                }
                break;
        }
        case IPC_MESSAGE_TYPE_RESPONSE: {
                switch (msg->payload.type) {
                case REQUEST_TYPE_WRITE_ACK:
                        printf("WRITE_ACK [");
                        for (size_t i = 0; i < msg->payload.size; i++) {
                                printf("%c", msg->payload.data[i]);
                        }
                        printf("]\n");
                        break;

                case REQUEST_TYPE_READ_ACK:
                        printf("READ_ACK [");
                        for (size_t i = 0; i < msg->payload.size; i++) {
                                printf("%c", msg->payload.data[i]);
                        }
                        printf("]\n");
                        break;
                
                default:
                        break;
                }
                break;
        }
        case IPC_MESSAGE_TYPE_TIMEOUT: {
                printf("TIMEOUT\n");
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

        if (now - last_request_ts > 3000) {
                last_request_ts = now;
                ipc_node_request(ipc, node, CONSUMER_NODE_ID, REQUEST_TYPE_WRITE, (uint8_t*)"to_write", 8, 100);
                ipc_node_request(ipc, node, CONSUMER_NODE_ID, REQUEST_TYPE_READ, (uint8_t*)"address", 7 , 200);
                ipc_node_request(ipc, node, CONSUMER_NODE_ID, REQUEST_TYPE_READ, NULL, 0, 2500);
        }
}
