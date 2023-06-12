#pragma warning (disable : 4100 4047 4024)

#include "ioctl_driver.h"
#include "communication.h"
#include "messages.h"
#include "events.h"
#include "data.h"


//driver setup
NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject,	PUNICODE_STRING pRegistryPath) {
	UNREFERENCED_PARAMETER(pRegistryPath);

	pDriverObject->DriverUnload = UnloadDriver;

	//could it be done in communicatoin.c by iocontrol??
	PsSetLoadImageNotifyRoutine(ImageLoadCallback);

	RtlInitUnicodeString(&dev, L"\\Device\\ioctldriver");
	RtlInitUnicodeString(&dos, L"\\??\\ioctldriverlink"); //this one is needed for UM app to connect

	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	DebugMessage("device address: %x", &pDeviceObject);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject) {

	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);

	DebugMessage("Driver unloaded!\n");

	return STATUS_SUCCESS;
}
