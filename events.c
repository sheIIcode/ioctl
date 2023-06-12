#pragma warning (disable : 4047)

#include "events.h"
#include "messages.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PCUNICODE_STRING FullImageName,
	HANDLE ProcessId,
	PIMAGE_INFO ImageInfo) {

	if (wcsstr(FullImageName->Buffer, L"\\bin_win32\\ac_client.exe")) {
		DebugMessage("dll found!\n");

		DLLAddress = ImageInfo->ImageBase;
		DriverStoredProcessId = ProcessId;

		DebugMessage("ProcessID : %d \n", ProcessId);
	}

	return STATUS_SUCCESS;
}