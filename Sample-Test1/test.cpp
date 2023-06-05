#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;

class DeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));

};

TEST(DeviceRead, Read5Times)
{
	DeviceMock device_mock;
	EXPECT_CALL(device_mock, read).Times(5);

	DeviceDriver drive(&device_mock);
	drive.read(0xA);

}

TEST(DeviceRead, ReadException)
{
	DeviceMock device_mock;
	EXPECT_CALL(device_mock, read)
	.WillOnce(Return(7))
	.WillOnce(Return(7))
	.WillOnce(Return(7))
	.WillOnce(Return(7))
	.WillOnce(Return(5));


	DeviceDriver drive(&device_mock);
	EXPECT_THROW(drive.read(0xA), std::exception);
}