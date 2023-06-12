#include <Windows.h>
#include <iostream>
#include "kernelinterface.hpp"

int main() {
	KernelInterface driver = KernelInterface("\\\\.\\ioctldriverlink");

	ULONG address = driver.GetClientAddress();
	ULONG processId = driver.GetProcessId();

	std::cout << processId << " "<< std::hex << address << std::endl;
	uint32_t readAddr = 0x0080f794;

	while (true) {
		uint8_t hp = driver.ReadVirtualMemory<uint8_t>(processId, readAddr, 1);

		std::cout << hp << std::endl;
		std::cout << (int)hp << std::endl;

		bool result  = driver.WriteVirtualMemory(processId, readAddr, 254, 1);

		if (result == false)
			std::cout << "ioctl_controller | failed to write memory" << std::endl;

		Sleep(500);

	}

	return 0;
}