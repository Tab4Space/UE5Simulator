// Fill out your copyright notice in the Description page of Project Settings.

#include "FAWorkerThread.h"

#include "FABaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "FAGameInstance.h"
#include "FAGameModeBase.h"
#include "FASharedMemory.h"
#include "Windows/WindowsHWrapper.h"

FAWorkerThread::FAWorkerThread(AGameModeBase* GameModeBase)
{
	FAGameModeBase = Cast<AFAGameModeBase>(GameModeBase);
	FAGameInstance = Cast<UFAGameInstance>(FAGameModeBase->GetGameInstance());

	//new FASharedMemory(FString("aa"));

	_hUESemaphore = CreateSemaphore(NULL, 0, 1, UE_SERVER_SEMAPHORE);
	_hPYSemaphore = CreateSemaphore(NULL, 0, 1, PY_CLIENT_SEMAPHORE);
}

FAWorkerThread::~FAWorkerThread()
{
	CloseHandle(_hUESemaphore);
	CloseHandle(_hPYSemaphore);
	FALOG_S(Warning)
}

bool FAWorkerThread::Init()
{
	FALOG(Warning, TEXT("Worker Thread Init"))
	if(_hUESemaphore && _hPYSemaphore)
	{
		FALOG(Warning, TEXT("Semaphore Success"))
		return true;
	}
	FALOG(Warning, TEXT("Semaphore Fail"))
	return false;
}

uint32 FAWorkerThread::Run()
{
	bool bFirstTime = true;
	int32 count = 0;
	
	while(bRunThread)
	{
		if(bFirstTime)
		{
			count++;
			WriteToMemory();
			Acquire();
			Release();
			bFirstTime = false;
		}
		else
		{
			count++;
			Acquire();
			ReadFromMemory();
			WriteToMemory();
			Release();
		}
	}
	FALOG(Warning, TEXT("%d"), count)
	return 0;
}

void FAWorkerThread::Stop()
{
	FRunnable::Stop();
}

void FAWorkerThread::Acquire()
{
	FALOG_S(Warning)
	int32 result = WaitForSingleObject(_hUESemaphore, INFINITE);
	if(result == WAIT_OBJECT_0)
	{
		//ReadFromMemory();
		//WriteToMemory();
	}
}

void FAWorkerThread::Release()
{
	FALOG_S(Warning)
	ReleaseSemaphore(_hPYSemaphore, 1, NULL);
}

void FAWorkerThread::WriteToMemory()
{
	FALOG(Warning, TEXT("Write Data"))
	for(auto agent : FAGameModeBase->Agents)
	{
		FString MemPath = agent->CharName + "_state";
		// TODO
		// require to agent that collect a data
		agent->GetState();
		FMemory::Memcpy(FAGameModeBase->Memory[MemPath], &agent->StateMessage, 32);
	}
}

void FAWorkerThread::ReadFromMemory()
{
	for (auto agent : FAGameModeBase->Agents)
	{
		FString MemPath = agent->CharName + "_action";
		FMemory::Memcpy(&agent->ActionMessage, FAGameModeBase->Memory[MemPath], 32);
		//TODO
		// request to agent that act

		if(agent->ControlType == 1)
		{
			agent->ExecSkill(agent->ActionMessage.SkillNumber);
		}

		
		
	}
}

void FAWorkerThread::SetbRunThread(bool bRunning)
{
	bRunThread = bRunning;
}

