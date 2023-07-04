// Copyright Epic Games, Inc. All Rights Reserved.


#include "FAGameModeBase.h"
#include "FAGameInstance.h"
#include "Windows/WindowsHWrapper.h"
#include "FAWorkerThread.h"
#include "HAL/RunnableThread.h"
#include "FABaseCharacter.h"
#include "GameSetting.h"
#include "Kismet/GameplayStatics.h"
#include "FAPlayerController.h"
#include "FASharedMemory.h"
#include "FASkillComponent.h"
#include "FAStatComponent.h"
#include "UObject/ConstructorHelpers.h"


AFAGameModeBase::AFAGameModeBase()
{
	// DefaultPawnClass = AFABaseCharacter::StaticClass();
	PlayerControllerClass = AFAPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<AFABaseCharacter> BP_Berserker(TEXT("/Game/Blueprints/Characters/BP_Berserker"));
	if(BP_Berserker.Succeeded() && BP_Berserker.Class != NULL)
	{
		CharacterTypeMap.Add(0, BP_Berserker.Class);
	}

	static ConstructorHelpers::FClassFinder<AFABaseCharacter> BP_Blade(TEXT("/Game/Blueprints/Characters/BP_Blade"));
	if(BP_Blade.Succeeded() && BP_Blade.Class != NULL)
	{
		CharacterTypeMap.Add(1, BP_Blade.Class);
	}

	static ConstructorHelpers::FClassFinder<AFABaseCharacter> BP_Sorceress(TEXT("/Game/Blueprints/Characters/BP_Sorceress"));
	if(BP_Sorceress.Succeeded() && BP_Sorceress.Class != NULL)
	{
		CharacterTypeMap.Add(2, BP_Sorceress.Class);
	}
}

void AFAGameModeBase::StartPlay()
{
	FindArkInstance = Cast<UFAGameInstance>(GetGameInstance());
	if(!FindArkInstance)
		FALOG(Fatal, TEXT("Not found FindArk Instance"));
	
	switch(FindArkInstance->GetPlayMode())
	{
		case 0:
		{
			FALOG(Warning, TEXT("Play the delvelopment mode"));
			break;
		}
		case 1:
		{
			FALOG(Warning, TEXT("Play the human control mode"));
			break;
		}
		case 2:
		{
			FALOG(Warning, TEXT("Play the deep learning mode"));
			if(!FindArkInstance->GetInGameThread())
			{
				WorkerThread = new FAWorkerThread(this);
				_hOpenSemaphore = OpenSemaphore(EVENT_ALL_ACCESS, false, LOADING_SEMAPHORE);
				ReleaseSemaphore(_hOpenSemaphore, 1, NULL);
				FALOG(Warning, TEXT("Create Worker Thread and Open Semaphore"));
				break;
			}
		}
		default: break;
	}

	SpawnCharacters();
	Super::StartPlay();
}

void AFAGameModeBase::BeginPlay()
{
	//CurrentWorkingThread = FRunnableThread::Create(WorkerThread, TEXT("WorkerThread"));
	Super::BeginPlay();
}

void AFAGameModeBase::OnPostLogin(AController* NewPlayer)
{
	FALOG_S(Warning)
	Super::OnPostLogin(NewPlayer);
}

void AFAGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// TODO
	// Close Handle(semaphore, memory mapping...)
	// kill thread
	// make log
	if(WorkerThread && CurrentWorkingThread)
	{
		CurrentWorkingThread->Suspend(true);
		WorkerThread->SetbRunThread(false);
		CurrentWorkingThread->Suspend(false);
		CurrentWorkingThread->Kill();
		CurrentWorkingThread->WaitForCompletion();
		delete WorkerThread;
		delete CurrentWorkingThread;
	}
	Super::EndPlay(EndPlayReason);
	
}

void AFAGameModeBase::SpawnCharacters()
{
	int32 PlayerIndex = 0;

	for(auto CharacterProperty : FindArkInstance->GetSettingData().Characters)
	{
		
		AFABaseCharacter* Character = GetWorld()->SpawnActorDeferred<AFABaseCharacter>(
			CharacterTypeMap[CharacterProperty.CharacterType],
			FTransform(FVector(100.f, 100.f, 200.f))
		);

		FALOG_S(Warning);
		if(Character)
		{
			Character->InitCharacter(PlayerIndex);
			Character->StatComponent->InitStatData();
			Character->SkillComponent->InitSkillData();
			UGameplayStatics::FinishSpawningActor(Character, FTransform(FVector(0.f, 0.f, 200.f)));
		}
		Agents.Add(Character);
		PlayerIndex++;
	}
}

FString AFAGameModeBase::MakeKey(const FString& AgentName)
{
	return FString("");
}

unsigned char* AFAGameModeBase::MallocShm(const FString& KeyName, unsigned int BufferSize)
{
	auto SharedMemory = new FASharedMemory(KeyName, BufferSize);
	Memory.Add(KeyName, SharedMemory->GetMemoryPtr());
	return Memory[KeyName];
}


