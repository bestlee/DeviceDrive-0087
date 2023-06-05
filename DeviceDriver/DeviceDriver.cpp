#include "DeviceDriver.h"
#include <exception>
#include <Windows.h>
DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int nReadValue = m_hardware->read(address);
	for (int nReadCount = 2 ; nReadCount <= VALID_READ_RETRY_COUNT ; nReadCount++)
    {
        Sleep(INTERVAL_READ);
        int nNextReadValue = m_hardware->read(address);
        if (nNextReadValue != nReadValue) throw std::exception("Exception");
    }
    return nReadValue;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}