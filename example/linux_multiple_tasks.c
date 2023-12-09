#include "freeipc.h"

#include "common.h"

#include <pthread.h>
#include <unistd.h>

static pthread_t g_consumer_thread;
static pthread_t g_producer_thread;

extern const struct ipc_hal_interface g_ipc_hal_interface_linux;

static const struct ipc_descriptor g_ipc_desc = {
        .name = "ipc",
        .hal = &g_ipc_hal_interface_linux,
};

static struct ipc_manager g_ipc;

static void* consumer_task_function(void *ptr)
{
        for (;;) {
                ipc_node_service(&g_ipc, &g_consumer_node, IPC_TIME_WAIT_FOREVER);
        }

        return NULL;
}

static void* producer_task_function(void *ptr)
{
        for (;;) {
                ipc_node_service(&g_ipc, &g_producer_node, 10);
        }

        return NULL;
}

int main(int argc, char *argv[])
{
        ipc_init(&g_ipc, &g_ipc_desc, NULL);

        ipc_node_register(&g_ipc, &g_producer_node, &g_producer_node_desc, NULL);
        ipc_node_register(&g_ipc, &g_consumer_node, &g_consumer_node_desc, NULL);

        pthread_create(&g_consumer_thread, NULL, consumer_task_function, NULL);
        pthread_create(&g_producer_thread, NULL, producer_task_function, NULL);

        for (;;) {
                ipc_service(&g_ipc, IPC_TIME_WAIT_FOREVER);
        }
}
