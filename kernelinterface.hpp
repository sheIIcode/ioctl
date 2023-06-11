#pragma once

#include <iostream>
#include "communication.hpp"

class KernelInterface {
public:
	HANDLE hDriver;

	KernelInterface(LPCSTR RegistryPath) {
		hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	
	}

	DWORD GetClientAddress() {
		if (hDriver == INVALID_HANDLE_VALUE) {
			std::cout << "failed to create file\n";
			return 0;
		}


		ULONG Address;
		DWORD Bytes;

		if (DeviceIoControl(hDriver, IO_GET_CLIENTADDRESS, &Address, sizeof(Address), &Address, sizeof(Address), &Bytes, NULL)) {
			std::cout << "address retrieved " << Address << std::endl;
			return Address;
		}

		return 0;
	}
};