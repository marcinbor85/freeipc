#include "freeipc.h"

#include "common.h"

extern const struct ipc_hal_interface *g_ipc_hal_interface_linux;

int main(int argc, char *argv[])
{
        ipc_init(&g_ipc, g_ipc_hal_interface_linux, NULL);

        ipc_node_register(&g_ipc, &g_producer_node, &g_producer_node_desc, NULL);
        ipc_node_register(&g_ipc, &g_consumer_node, &g_consumer_node_desc, NULL);

        for (;;) {
                ipc_service(&g_ipc, 10);

                ipc_node_service(&g_ipc, &g_producer_node, IPC_TIME_NO_WAIT);
                ipc_node_service(&g_ipc, &g_consumer_node, IPC_TIME_NO_WAIT);
        }
}
