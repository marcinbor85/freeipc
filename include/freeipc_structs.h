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

struct ipc_message_payload {
        uint32_t type;
        size_t size;
        uint8_t data[];
};

struct ipc_message_header {
        uint32_t id;
        uint32_t source_node_id;
        uint32_t dest_node_id;
        uint32_t create_timestamp;
        uint32_t timeout;
};

struct ipc_message {
        struct ipc_message_header header;
        ipc_message_type_t type;
        union {
                struct ipc_message_control control;
                struct ipc_message_notify notify;
                struct ipc_message_payload payload;
        };
};

struct ipc_node_descriptor {
        uint32_t id;

        ipc_node_message_hook_t message_hook;
        ipc_node_idle_hook_t idle_hook;
};

struct ipc_node {
        struct ipc_node *next;
        struct ipc_node_descriptor const *desc;
        ipc_node_state_t state;
        void *fifo;
        
        void *context;
};

struct ipc_pending_message {
        struct ipc_pending_message *next;
        struct ipc_message_header header;
};

struct ipc_manager {
        struct ipc_node *nodes;
        struct ipc_pending_message *pending_messages;
        struct ipc_hal_interface const *hal;
        uint32_t message_id_cntr;
        void *context;
        void *fifo;
        void *mutex;
};

#ifdef __cplusplus
}
#endif

#endif /* __FREEIPC_STRUCTS_H__ */
