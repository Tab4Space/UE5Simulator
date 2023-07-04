// Fill out your copyright notice in the Description page of Project Settings.


#include "FAPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "FABaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "FAGameModeBase.h"
#include "FASkillComponent.h"
#include "SkillData.h"
#include "TimerManager.h"
#include "FAEnums.h"


AFAPlayerController::AFAPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AFAPlayerController::BeginPlay()
{
	AFAGameModeBase* FAGameMode = Cast<AFAGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	FALOG_S(Warning)
	if(FAGameMode != nullptr)
	{
		for(auto agent : FAGameMode->Agents)
		{
			if(agent->ControlType == 0)
			{
				Possess(agent);
				break;
			}
		}
	}

	SkillExtrDataTable = ControlledCharacter->SkillComponent->GetSkillExtraDataTable();
	
	if(ControlledCharacter == nullptr)
	{
		SetViewTargetWithBlend(FAGameMode->Agents[0]);
	}
	Super::BeginPlay();
}

void AFAPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if(bInputPressed)
	{
		FollowTime += DeltaTime;

		// Look for the touch location
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;
		// Direct the Pawn towards that location

		if(ControlledCharacter)
		{
			FVector WorldDirection = (HitLocation - ControlledCharacter->GetActorLocation()).GetSafeNormal();
			ControlledCharacter->AddMovementInput(WorldDirection, 1.f, false);
		}
	}
	else
	{
		FollowTime = 0.f;
	}
}

void AFAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AFAPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AFAPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("SkillSlotQ", IE_Pressed, this, &AFAPlayerController::ExecSlotQ);
	InputComponent->BindAction("SkillSlotW", IE_Pressed, this, &AFAPlayerController::ExecSlotW);
	InputComponent->BindAction("SkillSlotE", IE_Pressed, this, &AFAPlayerController::ExecSlowE);
	InputComponent->BindAction("SkillSlotR", IE_Pressed, this, &AFAPlayerController::ExecSlowR);
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AFAPlayerController::PressLeftClick);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AFAPlayerController::ReleaseLeftClick);
}

void AFAPlayerController::OnPossess(APawn* InPawn)
{
	ControlledCharacter = Cast<AFABaseCharacter>(InPawn);
	Super::OnPossess(InPawn);

	if(ControlledCharacter != nullptr)
		FALOG(Warning, TEXT("%s"), *ControlledCharacter->GetName())
}

void AFAPlayerController::OnSetDestinationPressed()
{
	if(ControlledCharacter != nullptr)
	{
		bInputPressed = true;
		ControlledCharacter->CharacterCondition = ECharacterCondition::E_Idle;
		StopMovement();
	}
}

void AFAPlayerController::OnSetDestinationReleased()
{
	if(ControlledCharacter != nullptr)
	{
		// Player is no longer pressing the input
		bInputPressed = false;

		// If it was a short press
		if(FollowTime <= ShortPressThreshold)
		{
			// We look for the location in the world where the player has pressed the input
			FVector HitLocation = FVector::ZeroVector;
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, true, Hit);
			HitLocation = Hit.Location;

			// We move there and spawn some particles
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
			ControlledCharacter->CharacterCondition = ECharacterCondition::E_Moving;
		
		}
	}
}

void AFAPlayerController::ExecSlotQ()
{
	if(bIsTraceTarget)
		return;
	
	if(ControlledCharacter != nullptr)
	{
		SkillNumber = ControlledCharacter->UsableSkillNumbers[0];
		ControlledCharacter->ExecSkill(SkillNumber);
	}
}

void AFAPlayerController::ExecSlotW()
{
	if(bIsTraceTarget)
		return;
	
	if(ControlledCharacter != nullptr)
	{
		SkillNumber = ControlledCharacter->UsableSkillNumbers[1];
		ControlledCharacter->ExecSkill(SkillNumber);
	}
}

void AFAPlayerController::ExecSlowE()
{
	if(bIsTraceTarget)
		return;
	
	if(ControlledCharacter != nullptr)
	{
		SkillNumber = ControlledCharacter->UsableSkillNumbers[2];
		ControlledCharacter->ExecSkill(SkillNumber);
	}
	
}

void AFAPlayerController::ExecSlowR()
{
	if(bIsTraceTarget)
		return;
	
	if(ControlledCharacter != nullptr)
	{
		SkillNumber = ControlledCharacter->UsableSkillNumbers[3];
		ControlledCharacter->ExecSkill(SkillNumber);
	}
}

void AFAPlayerController::PressLeftClick()
{
	if(SkillTargetLocation == false)
	{
		SkillTargetLocation = true;
	}
}

void AFAPlayerController::ReleaseLeftClick()
{
	if(SkillTargetLocation == true)
	{
		SkillTargetLocation = false;
		GetWorldTimerManager().ClearTimer(ClickTimerHandle);
	}
}

void AFAPlayerController::DoWork1()
{
	bIsTraceTarget = true;
	GetWorld()->GetTimerManager().SetTimer(ClickTimerHandle, FTimerDelegate::CreateLambda([&]()  {
		FHitResult Hit;
		if(SkillTargetLocation == false)
		{
			TraceSkillLocation = TraceMouseLocation();
		}
		else
		{
			TraceSkillLocation = TraceMouseLocation();
			ControlledCharacter->ExecSkill(SkillNumber);
			bIsTraceTarget = false;
			GetWorld()->GetTimerManager().ClearTimer(ClickTimerHandle);	
		}
	}), 0.01, true);
}

FVector AFAPlayerController::TraceMouseLocation()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	return Hit.Location;
}
