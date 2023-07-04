// Fill out your copyright notice in the Description page of Project Settings.


#include "FABaseCharacter.h"
#include "FAGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "FAStatComponent.h"
#include "FASkillComponent.h"
#include "CharacterData.h"
#include "FAGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "FAPlayerController.h"


// Sets default values
AFABaseCharacter::AFABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->bHiddenInGame = false;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1600.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Stat component
	StatComponent = CreateDefaultSubobject<UFAStatComponent>(TEXT("StatComp"));

	// Skill Component
	SkillComponent = CreateDefaultSubobject<UFASkillComponent>(TEXT("SkillComp"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AFABaseCharacter::AllocateBuffer()
{
	AFAGameModeBase* FAGameModeBase = Cast<AFAGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	ActionBuffer = FAGameModeBase->MallocShm(CharName + "_action", 32);
	StateBuffer = FAGameModeBase->MallocShm(CharName + "_state", 32);
}

// Called when the game starts or when spawned
void AFABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	FALOG(Warning, TEXT("%s"), *NewController->GetName())
}


void AFABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(CharacterCondition == ECharacterCondition::E_Moving)
		SetCharacterMoving();
}

void AFABaseCharacter::InitCharacter(int32 PlayerIndex)
{
	UFAGameInstance* FAGameInstance = Cast<UFAGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	PlayerId	= PlayerIndex;
	CharName	= FAGameInstance->GetSettingData().Characters[PlayerId].CharacterName;
	ControlType = FAGameInstance->GetSettingData().Characters[PlayerId].ControlType;
	bIsEnemy	= FAGameInstance->GetSettingData().Characters[PlayerId].IsEnemy;
	UsableSkillNumbers = FAGameInstance->GetSettingData().Characters[PlayerId].UseSkills;
	AllocateBuffer();
}

void AFABaseCharacter::ExecSkill(int32 SkillNumber)
{
	// 1) 사용할 스킬이 스킬 슬롯 목록에 있나 확인
	// 2) 현재 스킬을 사용할 수 있는 상태인지 체크(다른 스킬을 쓰고있으면 못쓰게)
	// UsableSkillNumbers
	
	if(ControlType == 0)
	{
		if((UsableSkillNumbers.Contains(SkillNumber)) && (CharacterCondition!=ECharacterCondition::E_ExecutingSkill))
		{
			// 스킬은 skill component에서 관리
			// play montage
			// montage에서 애님노티파이
			// SkillComponent->PlaySkillMontage(SkillNumber);
			SkillComponent->ActivateSkill(SkillNumber);
		}
	}
}

void AFABaseCharacter::GetState()
{
	StateMessage.ID = PlayerId;
	StateMessage.Location = GetActorLocation();
}

void AFABaseCharacter::SetCharacterMoving()
{
	if(OnIsMoveingDelegate.IsBound() == true)
	{
		OnIsMoveingDelegate.Broadcast();
	}
}

