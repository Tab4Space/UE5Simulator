// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FINDARK_API FASharedMemory
{
public:
	FASharedMemory(const FString& MemoryName, unsigned int BufferSize);
	~FASharedMemory();
	
	void CloseShareMemory();

private:
	void*				_hMemory		= nullptr;		// Shared Memory Handle
	unsigned char*		_pMappedMemory	= nullptr;		// Mapping Memory Pointer
	int32				_MemSize		= 0;			// Mapping Memory Size

public:
	FORCEINLINE unsigned char*	GetMemoryPtr()		{ return _pMappedMemory; }		// Get pointer of memory mapped file
	FORCEINLINE int32			GetMemorySize()		{ return _MemSize; }			// Get size of memory mapped file

};
