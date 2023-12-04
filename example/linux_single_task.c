#include "freeipc.h"

#include "common.h"

#include <unistd.h>

extern const struct ipc_hal_interface *g_ipc_hal_interface_linux_no_threads;

int main(int argc, char *argv[])
{
        ipc_init(&g_ipc, g_ipc_hal_interface_linux_no_threads, NULL);

        ipc_node_register(&g_ipc, &g_producer_node, &g_producer_node_desc, NULL);
        ipc_node_register(&g_ipc, &g_consumer_node, &g_consumer_node_desc, NULL);

        for (;;) {
                ipc_service(&g_ipc, IPC_TIME_NO_WAIT);

                ipc_node_service(&g_ipc, &g_producer_node, IPC_TIME_NO_WAIT);
                ipc_node_service(&g_ipc, &g_consumer_node, IPC_TIME_NO_WAIT);

                // do something

                usleep(10000);
        }
}
