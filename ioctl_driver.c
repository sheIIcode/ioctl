#pragma warning (disable : 4100)

#include "ioctl_driver.h"
#include "messages.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, 
	PUNICODE_STRING pRegistryPath) {
	UNREFERENCED_PARAMETER(pDriverObject);
	UNREFERENCED_PARAMETER(pRegistryPath);

	//pDriverObject->DriverUnload = UnloadDriver;
	DbgPrintEx(0, 0, "helo fro m driver\n");

	DebugMessage("hello from driver dbg msg\n");

	return STATUS_SUCCESS;
}

//NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject) {
//	UNREFERENCED_PARAMETER(pDriverObject);
//
//	DebugMessage("Driver unloaded!\n");
//
//	return STATUS_SUCCESS;
//}
