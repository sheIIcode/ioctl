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
			std::cout << "kernelinterface | address retrieved " << std::hex 
				<< Address << std::endl;

			return Address;
		}

		return 0;
	}

	DWORD GetProcessId() {
		if (hDriver == INVALID_HANDLE_VALUE) {
			std::cout << "failed to create file\n";
			return 0;
		}

		ULONG ProcessId;
		DWORD Bytes;

		if (DeviceIoControl(hDriver, IO_GET_PROCESSID, &ProcessId, sizeof(ProcessId), &ProcessId, sizeof(ProcessId), &Bytes, NULL)) {
			std::cout << "kernelinterface | processid retrieved " << std::hex
				<< ProcessId << std::endl;

			return ProcessId;
		}

		return 0;
	}

	template <typename type>
	type ReadVirtualMemory(ULONG ProcessId, ULONG ReadAddress, SIZE_T Size) {
		type Buffer;

		KERNEL_READ_REQUEST ReadRequest;

		ReadRequest.ProcessId = ProcessId;
		ReadRequest.Address = ReadAddress;
		ReadRequest.pBuff = &Buffer;
		ReadRequest.Size = Size;

		if (DeviceIoControl(hDriver, IO_READ_REQUEST, &ReadRequest, sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), 0, 0)) {
			return Buffer;
		}

		return Buffer;
	}

	template <typename type>
	bool WriteVirtualMemory(ULONG ProcessId, ULONG WriteAddress, type WriteValue, SIZE_T Size) {
		
		if (hDriver == INVALID_HANDLE_VALUE) {
			return false;
		}

		DWORD Bytes;

		KERNEL_WRITE_REQUEST WriteRequest;

		WriteRequest.ProcessId = ProcessId;
		WriteRequest.Address = WriteAddress;
		WriteRequest.pBuff = &WriteValue;
		WriteRequest.Size = Size;

		if (DeviceIoControl(hDriver, IO_WRITE_REQUEST, &WriteRequest, sizeof(WriteRequest), 0, 0, &Bytes, NULL)) {
			return true;
		}

		return false;
	}
};