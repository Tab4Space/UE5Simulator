// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FAPlayerController.generated.h"

class AFABaseCharacter;
class UDataTable;

UCLASS()
class FINDARK_API AFAPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AFAPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3;

	UPROPERTY()
	AFABaseCharacter* ControlledCharacter = nullptr;
	FVector TraceMouseLocation();

protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void DoWork1();

	void ExecSlotQ();
	void ExecSlotW();
	void ExecSlowE();
	void ExecSlowR();
	void PressLeftClick();
	void ReleaseLeftClick();


public:
	UDataTable*			SkillExtrDataTable;
	FTimerHandle		ClickTimerHandle;
private:
	bool		bInputPressed;
	float		FollowTime;
	bool		SkillTargetLocation;
	bool		bIsTraceTarget;
	int32		SkillNumber;
	FVector		TraceSkillLocation;
};
