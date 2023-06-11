#pragma once

#include <ntifs.h>
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PCUNICODE_STRING FullImageName,
	HANDLE ProcessId,
	PIMAGE_INFO imageInfo);
