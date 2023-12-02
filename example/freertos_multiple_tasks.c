
#include "freeipc.h"

#include <stddef.h>



static struct ipc_node g_consumer_node;
static struct ipc_node g_producer_node;

static struct ipc g_ipc;

static void consumer_node_callback(struct ipc *ipc, void *context, struct ipc_message_item *msg)
{
        switch (msg->type) {
        case IPC_MESSAGE_TYPE_NOTIFY:
                msg->notify.value

                break;

        case IPC_MESSAGE_TYPE_REQUEST:

                if (msg->request.flags.need_response) {
                        // send response
                }
                break;
        }
}

static void consumer_node_task_service(void *params)
{
        ipc_register_node(&g_ipc, &g_consumer_node, 1, consumer_node_callback);

        for (;;) {
                ipc_node_service(&g_ipc, &g_consumer_node, 1000);

                // do something
        }
}

static void producer_node_callback(struct ipc *ipc, void *context, struct ipc_message_item *msg)
{
        switch (msg->type) {
        case IPC_MESSAGE_TYPE_RESPONSE:
                break;
        }
}

static void producer_node_task_service(void *params)
{
        ipc_register_node(&g_ipc, &g_producer_node, 1, producer_node_callback);

        for (;;) {
                ipc_node_service(&g_ipc, &g_producer_node, 1000);

                // do something
        }
}

static void ipc_task_service(void *params)
{
        for (;;) {
                ipc_service(&g_ipc, portMAX_DELAY);

                // do something
        }
}


int main(int argc, char *argv[])
{
        ipc_init(&ipc);

        while (1) {

        }
}
