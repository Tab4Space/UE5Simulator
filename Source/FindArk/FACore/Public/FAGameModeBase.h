// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FABaseCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "Message.h"
#include "FAGameModeBase.generated.h"

class UFAGameInstance;
class FAWorkerThread;
class AFABaseCharacter;
class FASharedMemory;

UCLASS()

class FINDARK_API AFAGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFAGameModeBase();

protected:
	virtual void StartPlay() override;		// start play는 다른 actor들의 begin play를 동작시킴.
	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void			SpawnCharacters();
	FString			MakeKey(const FString& AgentName);
	unsigned char*	MallocShm(const FString& KeyName, unsigned int BufferSize);
	
private:
	UPROPERTY()
	UFAGameInstance*	FindArkInstance = nullptr;
	
	FAWorkerThread*		WorkerThread = nullptr;
	FRunnableThread*	CurrentWorkingThread = nullptr;
	FMessage			Message = {44, FVector(9.f, 9.f, 9.f)};
	void*				_hOpenSemaphore = nullptr;

public:
	UPROPERTY()
	TArray<AFABaseCharacter*>		Agents;
	UPROPERTY(VisibleDefaultsOnly)
	TMap<int32, TSubclassOf<AFABaseCharacter>> CharacterTypeMap;

	TMap<FString, unsigned char*>	Memory;

public:
	FORCEINLINE FMessage* GetMessageAddr() { return &Message; }
	
	
};
