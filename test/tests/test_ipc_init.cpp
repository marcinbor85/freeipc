#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ipc_hal_mocks.hpp"

class IpcInit_Test : public ::testing::Test
{
protected:
        virtual void SetUp()
        {
                gMock_IpcHalInterface = new ::testing::StrictMock<IpcHalInterface_Mock>();
        }

        virtual void TearDown()
        {
                delete gMock_IpcHalInterface;
        }
};

TEST_F(IpcInit_Test, init)
{
        struct ipc_manager ipc {};

        EXPECT_CALL(*gMock_IpcHalInterface, ipc_hal_fifo_create(&ipc)).WillOnce(::testing::Return((void*)0x111));
        EXPECT_CALL(*gMock_IpcHalInterface, ipc_hal_mutex_create(&ipc)).WillOnce(::testing::Return((void*)0x222));

        ipc_init(&ipc, (struct ipc_hal_interface*)0x333, (void*)0x12345678);

        EXPECT_EQ(ipc.nodes, nullptr);
        EXPECT_EQ(ipc.hal, (struct ipc_hal_interface*)0x333);
        EXPECT_EQ(ipc.context, (void*)0x12345678);
        EXPECT_EQ(ipc.fifo, (void*)0x111);
        EXPECT_EQ(ipc.mutex, (void*)0x222);
}
