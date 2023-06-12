#pragma once


#include<ntifs.h>

NTSTATUS NTAPI
MmCopyVirtualMemory
(
    IN PEPROCESS SourceProcess,
    IN CONST VOID* SourceAddress,
    IN PEPROCESS TargetProcess,
    OUT PVOID TargetAddress,
    IN SIZE_T BufferSize,
    IN KPROCESSOR_MODE PreviousMode,
    OUT PSIZE_T ReturnSize
);


NTSTATUS KernelReadVirtualMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size);

NTSTATUS KernelWriteVirtualMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size);