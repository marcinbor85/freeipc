#include "freeipc.h"
#include "freeipc_hal.h"

#define IPC_LOG_TAG             "get_time"
#define IPC_LOG_TAG_LEVEL       IPC_LOG_LEVEL_DEBUG

#include "freeipc_log.h"
#include "freeipc_assert.h"

uint32_t ipc_get_time(struct ipc_manager *self)
{
        IPC_ASSERT(self != NULL);
        return self->desc->hal->get_time(self);
}
