#ifndef __FREEIPC_ENUMS_H__
#define __FREEIPC_ENUMS_H__

#ifdef __cplusplus
extern "C" {
#endif

// TODO: remove control
typedef enum {
        IPC_CONTROL_CMD_SUSPEND,
        IPC_CONTROL_CMD_RESUME,
        IPC_CONTROL_CMD__TOTAL_NUM
} ipc_control_cmd_t;

typedef enum {
        IPC_MESSAGE_TYPE_CONTROL,
        IPC_MESSAGE_TYPE_NOTIFY,
        IPC_MESSAGE_TYPE_REQUEST,
        IPC_MESSAGE_TYPE_RESPONSE,
        IPC_MESSAGE_TYPE_TIMEOUT,
        IPC_MESSAGE_TYPE__TOTAL_NUM
} ipc_message_type_t;

// TODO: remove state
typedef enum {
        IPC_NODE_STATE_NOT_REGISTERED,
        IPC_NODE_STATE_PAUSED,
        IPC_NODE_STATE_RUNNING,
        IPC_NODE_STATE__TOTAL_NUM
} ipc_node_state_t;

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_ENUMS_H__ */
