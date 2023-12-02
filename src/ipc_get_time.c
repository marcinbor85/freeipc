#include "freeipc.h"
#include "freeipc_hal.h"

uint32_t ipc_get_time(struct ipc_manager *self)
{
        return self->hal->get_time(self);
}
