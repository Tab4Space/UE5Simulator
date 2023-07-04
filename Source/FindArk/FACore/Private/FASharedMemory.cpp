// Fill out your copyright notice in the Description page of Project Settings.


#include "FASharedMemory.h"
#include "Windows/MinWindows.h"
#include "Windows/WindowsHWrapper.h"



FASharedMemory::FASharedMemory(const FString& MemoryName, unsigned int BufferSize)
{
	FString MemoryFullName = "FINDARK_SHAREDMEMORY_" + MemoryName;
	
		
	_hMemory = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		BufferSize,
		*MemoryFullName
	);

	if (_hMemory == nullptr)
		FALOG(Warning, TEXT("_hMemory Null"))

	_pMappedMemory = (uint8*)MapViewOfFile(
		_hMemory,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		BufferSize
	);

	if (_pMappedMemory == nullptr)
		FALOG(Warning, TEXT("_pMappedMemory Null"))

}

FASharedMemory::~FASharedMemory()
{
}

void FASharedMemory::CloseShareMemory()
{
	FALOG_S(Warning)
	CloseHandle(_hMemory);
	UnmapViewOfFile(_pMappedMemory);
}

