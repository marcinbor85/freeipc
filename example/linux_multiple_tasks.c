#include "freeipc.h"

#include "common.h"

#include <pthread.h>
#include <unistd.h>

static pthread_t g_ipc_thread;
static pthread_t g_consumer_thread;
static pthread_t g_producer_thread;

extern const struct ipc_hal_interface *g_ipc_hal_interface_linux;

static void* ipc_task_function(void *ptr)
{
        for (;;) {
                ipc_service(&g_ipc, IPC_TIME_WAIT_FOREVER);
        }

        return NULL;
}

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
        ipc_init(&g_ipc, g_ipc_hal_interface_linux, NULL);

        ipc_node_register(&g_ipc, &g_producer_node, &g_producer_node_desc, NULL);
        ipc_node_register(&g_ipc, &g_consumer_node, &g_consumer_node_desc, NULL);

        pthread_create(&g_ipc_thread, NULL, ipc_task_function, NULL);
        pthread_create(&g_consumer_thread, NULL, consumer_task_function, NULL);
        pthread_create(&g_producer_thread, NULL, producer_task_function, NULL);

        pthread_join(g_ipc_thread, NULL);
        pthread_join(g_consumer_thread, NULL);
        pthread_join(g_producer_thread, NULL);
}
