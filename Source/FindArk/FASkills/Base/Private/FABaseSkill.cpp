// Fill out your copyright notice in the Description page of Project Settings.


#include "FABaseSkill.h"
#include "Components/DecalComponent.h"
#include "FAPlayerController.h"
#include "FABaseCharacter.h"
#include "FAGameInstance.h"
#include "FASkillComponent.h"
#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AFABaseSkill::AFABaseSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	DecalComponent->SetupAttachment(RootComponent);
	DecalComponent->SetRelativeRotation({90.f, 0.f, 0.f});
	DecalComponent->SetHiddenInGame(true);
	IsSetTargetLocation = false;
}

// Called when the game starts or when spawned
void AFABaseSkill::BeginPlay()
{
	FAOwnerCharacter = Cast<AFABaseCharacter>(GetOwner());
	FAController = Cast<AFAPlayerController>(FAOwnerCharacter->GetController());
	
	// Bind delegate
	FAOwnerCharacter->OnIsMoveingDelegate.AddDynamic(this, &AFABaseSkill::SkillDestroy);
	// Spawn한 애가 DL 컨트롤이면 버퍼에서 값 가져오게
	switch (FAOwnerCharacter->GetControlType())
	{
	case 0:
		break;
	case 1:
		SkillTargetLocation = FAOwnerCharacter->ActionMessage.SkillTargetLoc;
		break;
	case 2:
		break;
	}

	if(FAController && IsTargettingSkill)
	{
		EnableInput(FAController);
		UInputComponent* myInputComp = this->InputComponent;
		if (myInputComp)
			SetupActorInputComponent(myInputComp);
	}

	if(FAOwnerCharacter && !IsTargettingSkill)
	{
		FAOwnerCharacter->SkillComponent->PlaySkillMontage();
	}

	Super::BeginPlay();
	SkillTargetLocation = GetActorLocation();
}

// Called every frame
void AFABaseSkill::Tick(float DeltaTime)
{
	if(FAController && IsTargettingSkill && !IsSetTargetLocation && !FAOwnerCharacter->IsMoving)
	{
		FHitResult Hit;
		FAController->GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		SetActorLocation(Hit.Location);
		SkillTargetLocation = Hit.Location;
	}
	Super::Tick(DeltaTime);
	
}

void AFABaseSkill::SetupActorInputComponent(UInputComponent* myInputComponent)
{
	myInputComponent->BindAction("LeftClick", IE_Pressed, this, &AFABaseSkill::SetTargetLocation);
}

void AFABaseSkill::SetTargetLocation()
{
	if(FAOwnerCharacter && FAOwnerCharacter->CharacterCondition != ECharacterCondition::E_ExecutingSkill)
	{
		DecalComponent->SetHiddenInGame(true);
		IsSetTargetLocation = true;
		FAOwnerCharacter->SkillComponent->PlaySkillMontage();	
	}
}

bool AFABaseSkill::TraceSphere(FVector OriginLocation, FVector Modifier)
{
	float Radius = Modifier.X;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	
	UFAGameInstance* FAGameInstance = Cast<UFAGameInstance>(GetGameInstance());
	if(FAGameInstance->GetDrawSkillDebug())
		DrawDebugSphere(GetWorld(), OriginLocation, Radius, 12, FColor::White, false, 5.f, 0, 5.f);

	bool IsOverlapped = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(), OriginLocation, Radius, ObjectTypes, nullptr, IgnoreActors, TraceResultActors
	);

	return IsOverlapped;
}

bool AFABaseSkill::TraceDonut(FVector OriginLocation, FVector Modifier)
{
	float OuterRadius = Modifier.X;
	float InnerRadius = Modifier.Y;
	TArray<AActor*> OutActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	
	UFAGameInstance* FAGameInstance = Cast<UFAGameInstance>(GetGameInstance());
	if(FAGameInstance->GetDrawSkillDebug())
	{
		DrawDebugSphere(GetWorld(), OriginLocation, OuterRadius, 12, FColor::Green, false, 5.f, 0, 5.f);
		DrawDebugSphere(GetWorld(), OriginLocation, InnerRadius, 12, FColor::Red, false, 5.f, 0, 5.f);
	}

	bool IsOverlapped = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		OriginLocation,
		OuterRadius,
		ObjectTypes,
		nullptr,
		IgnoreActors,
		OutActors
	);

	if(IsOverlapped)
	{
		for(auto OutActor : OutActors)
		{
			float Distance = GetDistanceTo(OutActor);
			if(Distance > InnerRadius)
				TraceResultActors.AddUnique(OutActor);
		}
	}
	return IsOverlapped;
}

bool AFABaseSkill::TraceeCone(FVector OriginLocation, FVector Modifier)
{
	float Radius = Modifier.X;
	float MinAngle = Modifier.Y;
	float MaxAngle = Modifier.Z;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	
	UFAGameInstance* FAGameInstance = Cast<UFAGameInstance>(GetGameInstance());
	if(FAGameInstance->GetDrawSkillDebug())
	{
		FVector a = FAOwnerCharacter->GetActorLocation();
		FVector b = FAOwnerCharacter->GetActorForwardVector();
		float c = FMath::DegreesToRadians(MaxAngle + FMath::Abs(MinAngle));
		float d = FMath::DegreesToRadians(1.f);
		DrawDebugCone(
			GetWorld(), a, b, 500.f,
			c, d, 12, FColor::White,
			false, 5.f, 0, 5
		);
	}

	bool IsOverlapped = UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		FVector::ZeroVector,
		Radius,
		ObjectTypes,
		nullptr,
		IgnoreActors,
		TraceResultActors
	);
	
	return IsOverlapped;
}

bool AFABaseSkill::TraceRectangle(FVector OriginLocation, FVector Modifier)
{
	float StartBias = Modifier.X;
	float Length = Modifier.Y;
	float HalfSize = Modifier.Z;
	
	FVector Start = FAOwnerCharacter->GetActorLocation() + (FAOwnerCharacter->GetActorForwardVector()*StartBias);
	FVector End = Start + (FAOwnerCharacter->GetActorForwardVector() * Length);
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Emplace(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	IgnoreActors.Add(GetOwner());
	
	TArray<FHitResult> HitResults;
	
	bool Result = UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetWorld(), Start, End,
		FVector(1.f, HalfSize, HalfSize), FAOwnerCharacter->GetActorRotation(),
		ObjectType, false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResults,
		true, FLinearColor::Red,FLinearColor::Green,	5.f
	);
	
	for(auto HitResult : HitResults)
	{
		if(IsValid(HitResult.GetActor()))
		{
			TraceResultActors.AddUnique(HitResult.GetActor());
			FALOG(Warning, TEXT("%s"), *HitResult.GetActor()->GetName())
		}
	}
	return Result;
}

bool AFABaseSkill::TraceCylinder(FVector OriginLocation, FVector Modifier)
{
	float StartBias = Modifier.X;
	float Length = Modifier.Y;
	float Radius = Modifier.Z;
	
	FVector Start = FAOwnerCharacter->GetActorLocation() + (FAOwnerCharacter->GetActorForwardVector()*StartBias);
	FVector End = Start + (FAOwnerCharacter->GetActorForwardVector() * Length);
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Emplace(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	IgnoreActors.Add(GetOwner());
	
	TArray<FHitResult> HitResults;
	
	bool Result = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(), Start, End,
		Radius, ObjectType, false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResults,
		true, FLinearColor::Red,FLinearColor::Green,	5.f
	);
	
	for(auto HitResult : HitResults)
	{
		if(IsValid(HitResult.GetActor()))
		{
			TraceResultActors.AddUnique(HitResult.GetActor());
			FALOG(Warning, TEXT("%s"), *HitResult.GetActor()->GetName())
		}
	}
	return Result;
}

void AFABaseSkill::SkillDestroy()
{
	FALOG(Warning, TEXT("Skill Destroy"))
	Destroy();
}

void AFABaseSkill::OnBeginDamage(ETraceType TraceType, FVector Modifier)
{
	FALOG_S(Warning)
	switch (TraceType)
	{
	case ETraceType::E_TraceSphere:
		TraceSphere(SkillTargetLocation, Modifier);
		break;
	case ETraceType::E_TraceCone:
		TraceeCone(SkillTargetLocation, Modifier);
		break;
	case ETraceType::E_TraceRectangle:
		TraceRectangle(SkillTargetLocation, Modifier);
		break;
	case ETraceType::E_TraceCylinder:
		TraceCylinder(SkillTargetLocation, Modifier);
		break;
	default:
		{
			break;	
		}
	}
}

void AFABaseSkill::OnEndDamage()
{
	
}

void AFABaseSkill::ApplySkillDamage()
{
	
}
