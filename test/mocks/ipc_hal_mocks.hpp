#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "freeipc_internal.h"

struct IpcHalInterface
{
        virtual uint32_t ipc_hal_get_time(struct ipc_manager *self) = 0;
        virtual void* ipc_hal_malloc(struct ipc_manager *self, size_t size) = 0;
        virtual void ipc_hal_free(struct ipc_manager *self, void *ptr) = 0;
        virtual void* ipc_hal_mutex_create(struct ipc_manager *self) = 0;
        virtual void ipc_hal_mutex_lock(struct ipc_manager *self, void *mutex) = 0;
        virtual void ipc_hal_mutex_unlock(struct ipc_manager *self, void *mutex) = 0;
        virtual void* ipc_hal_fifo_create(struct ipc_manager *self) = 0;
        virtual bool ipc_hal_fifo_get_item(struct ipc_manager *self, void *fifo, void **item, uint32_t max_wait_time) = 0;
        virtual bool ipc_hal_fifo_put_item(struct ipc_manager *self, void *fifo, void *item) = 0;
};

struct IpcHalInterface_Mock : public IpcHalInterface
{
        MOCK_METHOD(uint32_t, ipc_hal_get_time, (struct ipc_manager *self), (override));
        MOCK_METHOD(void*, ipc_hal_malloc, (struct ipc_manager *self, size_t size), (override));
        MOCK_METHOD(void, ipc_hal_free, (struct ipc_manager *self, void *ptr), (override));
        MOCK_METHOD(void*, ipc_hal_mutex_create, (struct ipc_manager *self), (override));
        MOCK_METHOD(void, ipc_hal_mutex_lock, (struct ipc_manager *self, void *mutex), (override));
        MOCK_METHOD(void, ipc_hal_mutex_unlock, (struct ipc_manager *self, void *mutex), (override));
        MOCK_METHOD(void*, ipc_hal_fifo_create, (struct ipc_manager *self), (override));
        MOCK_METHOD(bool, ipc_hal_fifo_get_item, (struct ipc_manager *self, void *fifo, void **item, uint32_t max_wait_time), (override));
        MOCK_METHOD(bool, ipc_hal_fifo_put_item, (struct ipc_manager *self, void *fifo, void *item), (override));
};

::testing::StrictMock<IpcHalInterface_Mock> *gMock_IpcHalInterface;

extern "C" {

uint32_t ipc_hal_get_time(struct ipc_manager *self)
{
        return gMock_IpcHalInterface->ipc_hal_get_time(self);
}

void* ipc_hal_malloc(struct ipc_manager *self, size_t size)
{
        return gMock_IpcHalInterface->ipc_hal_malloc(self, size);
}

void ipc_hal_free(struct ipc_manager *self, void *ptr)
{
        gMock_IpcHalInterface->ipc_hal_free(self, ptr);
}

void* ipc_hal_mutex_create(struct ipc_manager *self)
{
        return gMock_IpcHalInterface->ipc_hal_mutex_create(self);
}

void ipc_hal_mutex_lock(struct ipc_manager *self, void *mutex)
{
        gMock_IpcHalInterface->ipc_hal_mutex_lock(self, mutex);
}

void ipc_hal_mutex_unlock(struct ipc_manager *self, void *mutex)
{
        gMock_IpcHalInterface->ipc_hal_mutex_unlock(self, mutex);
}

void* ipc_hal_fifo_create(struct ipc_manager *self)
{
        return gMock_IpcHalInterface->ipc_hal_fifo_create(self);
}

bool ipc_hal_fifo_get_item(struct ipc_manager *self, void *fifo, void **item, uint32_t max_wait_time)
{
        return gMock_IpcHalInterface->ipc_hal_fifo_get_item(self, fifo, item, max_wait_time);
}

bool ipc_hal_fifo_put_item(struct ipc_manager *self, void *fifo, void *item)
{
        return gMock_IpcHalInterface->ipc_hal_fifo_put_item(self, fifo, item);
}

}
