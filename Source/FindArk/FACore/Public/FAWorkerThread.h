// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"

class AFAGameModeBase;
class UFAGameInstance;


class FINDARK_API FAWorkerThread : public FRunnable
{
public:
	FAWorkerThread(AGameModeBase* GameModeBase);
	~FAWorkerThread();

	// Overriden from FRunnable
	// Do not call these functions youself, that will happen automatically (FRunnableThread::Create -> Init -> Run)
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

protected:
	void Acquire();
	void Release();
	void WriteToMemory();
	void ReadFromMemory();
	

private:
	FRunnableThread*		Thread			= nullptr;
	AFAGameModeBase*		FAGameModeBase	= nullptr;
	UFAGameInstance*		FAGameInstance	= nullptr;
	
	void*					_hUESemaphore;		// Unreal Semaphore Handle
	void*					_hPYSemaphore;		// Python Semaphore Handle
	
	bool bRunThread = true;

public:
	void SetbRunThread(bool bRunning);
	
};
