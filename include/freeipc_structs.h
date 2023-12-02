#ifndef __FREEIPC_STRUCTS_H__
#define __FREEIPC_STRUCTS_H__

#include <stdint.h>
#include <stddef.h>

#include "freeipc_enums.h"
#include "freeipc_hal.h"
#include "freeipc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ipc_message_control {
        ipc_control_cmd_t cmd;
};

struct ipc_message_notify {
        uint32_t value;
        void *args;
};

struct ipc_message_request {
        uint32_t timeout_value;
        size_t payload_size;
        uint8_t payload[5];
};

struct ipc_message_response {
        size_t payload_size;
        uint8_t payload[5];
};

struct ipc_message {
        uint32_t id;
        uint32_t source_node_id;
        uint32_t dest_node_id;
        uint32_t create_timestamp;
        ipc_message_type_t type;
        union {
                struct ipc_message_control control;
                struct ipc_message_notify notify;
                struct ipc_message_request request;
                struct ipc_message_response response;
        };
};

struct ipc_message_list {
        struct ipc_message_list *next;
        struct ipc_message *msg;
};

struct ipc_node {
        uint32_t id;
        ipc_node_state_t state;
        struct ipc_message_list *active_messages;
        void *fifo;

        ipc_node_service_func_t service_func;
        void *context;
};

struct ipc_node_list {
        struct ipc_node_list *next;
        struct ipc_node *node;
};

struct ipc_manager {
        struct ipc_node_list *nodes;
        struct ipc_hal_interface const *hal;
        void *context;
        void *fifo;
        void *mutex;
};

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_STRUCTS_H__ */
