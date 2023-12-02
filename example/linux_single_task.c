
#include "freeipc.h"

#include <stdio.h>

static struct ipc_node g_consumer_node;
static struct ipc_node g_producer_node;

static struct ipc_manager g_ipc;

#define PRODUCER_NODE_ID        1
#define CONSUMER_NODE_ID        2

extern const struct ipc_hal_interface *g_ipc_hal_interface_linux_no_threads;

static void consumer_node_service(struct ipc_manager *ipc, struct ipc_node *node, struct ipc_message *msg)
{
        static int request_cntr = 0;

        if (msg == NULL)
                return;

        switch (msg->type) {
        case IPC_MESSAGE_TYPE_NOTIFY: {
                printf("notify received from %d: value = 0x%04X\n", msg->source_node_id, (uint16_t)msg->notify.value);
                break;
        }

        case IPC_MESSAGE_TYPE_REQUEST: {
                printf("request received from %d: payload = ", msg->source_node_id);
                for (int i = 0; i < msg->request.payload_size; i++) {
                        printf("%c", msg->request.payload[i]);
                }
                printf("\n");

                request_cntr++;
                if (request_cntr % 5 != 0) {
                        printf("send response\n");
                        ipc_node_response(ipc, node, msg, NULL, 0);
                } else {
                        printf("no response\n");
                }
                
                break;
        }
        default:
                break;
        }
}

static void producer_node_service(struct ipc_manager *ipc, struct ipc_node *node, struct ipc_message *msg)
{
        static uint32_t last_notify_ts = 0;
        static uint32_t last_request_ts = 0;

        uint32_t now = ipc_get_time(ipc);
        
        if (now - last_notify_ts > 1000) {
                last_notify_ts = now;
                ipc_node_notify(ipc, node, CONSUMER_NODE_ID, 0x1234, NULL);
        }
        if (now - last_request_ts > 3000) {
                last_request_ts = now;
                ipc_node_request(ipc, node, CONSUMER_NODE_ID, (uint8_t*)"abc", 3, 100);
        }

        if (msg == NULL)
                return;

        switch (msg->type) {
        case IPC_MESSAGE_TYPE_RESPONSE: {
                printf("response received\n");
                break;
        }
        default:
                break;
        }
}

int main(int argc, char *argv[])
{
        ipc_init(&g_ipc, g_ipc_hal_interface_linux_no_threads, NULL);

        ipc_node_register(&g_ipc, &g_producer_node, PRODUCER_NODE_ID, producer_node_service, NULL);
        ipc_node_register(&g_ipc, &g_consumer_node, CONSUMER_NODE_ID, consumer_node_service, NULL);

        for (;;) {
                ipc_service(&g_ipc, 0);

                ipc_node_service(&g_ipc, &g_producer_node, 0);
                ipc_node_service(&g_ipc, &g_consumer_node, 0);

                // do something
        }
}
