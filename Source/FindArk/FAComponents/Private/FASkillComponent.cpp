#include "FASkillComponent.h"
#include "FAGameInstance.h"
#include "FABaseCharacter.h"
#include "FAPlayerController.h"
#include "TimerManager.h"
#include "Animation/AnimInstance.h"
#include "Components/DecalComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"
#include "Kismet/KismetMathLibrary.h"


UFASkillComponent::UFASkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	for(int32 i = 1; i < 9; i++)
	{
		SkillDatas.Add(i);

		FTimerHandle CoolTimeHandle;
		SkillTimerHandleMap.Add(i, CoolTimeHandle);
	}

}


// Called when the game starts
void UFASkillComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SkillTimerManagerHandle, this, &UFASkillComponent::GetRemainCoolTime, 1.f, true);
}

// Called every frame
void UFASkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFASkillComponent::InitSkillData()
{
	UFAGameInstance* FAGameInstance = Cast<UFAGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	OwnerCharacter = Cast<AFABaseCharacter>(GetOwner());

	if(FAGameInstance && OwnerCharacter)
	{
		int32 NumOfSkill = FAGameInstance->GetSettingData().Characters[OwnerCharacter->PlayerId].Skills.Num();
		for(int32 i = 0; i < NumOfSkill; i++)
		{
			// From json file
			FSkillData temp = FAGameInstance->GetSettingData().Characters[OwnerCharacter->PlayerId].Skills[i];
			SkillDatas.Find(i+1)->SkillNumber	= temp.SkillNumber;
			SkillDatas.Find(i+1)->SkillName		= temp.SkillName;
			SkillDatas.Find(i+1)->DamageFactor	= temp.DamageFactor;
			SkillDatas.Find(i+1)->CoolTime		= temp.CoolTime;
			SkillDatas.Find(i+1)->CostMana		= temp.CostMana;
		}
	}
}

void UFASkillComponent::ActivateSkill(int32 SkillNumber)
{
	CurrentSkillNumber = SkillNumber;
	
	if(SkillExtrDataTable == nullptr)
		return;

	CurrentSkillExtraData = *(SkillExtrDataTable->FindRow<FSkillExtraData>(*FString::FromInt(SkillNumber), TEXT("")));

	if(CurrentSkillExtraData.IsRotateToCursor)
	{
		// 캐릭터 rotate to cursur
		FVector LocationToRotate = RotateToTarget();
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), LocationToRotate);
		FRotator NewRotation = UKismetMathLibrary::RInterpTo(OwnerCharacter->GetActorRotation(), TargetRotation, 0.5f, 3.f);
		OwnerCharacter->SetActorRotation(FRotator(0.f, NewRotation.Yaw, 0.f));
	}
	
	if(CurrentSkillExtraData.Skill)
	{
		float RemainTime = GetWorld()->GetTimerManager().GetTimerRemaining(SkillTimerHandleMap[CurrentSkillNumber]);
		FALOG(Warning, TEXT("%f"), RemainTime)
		if(RemainTime <= 0)
		{
			FALOG_S(Warning)
			SpawnSkill();
		}
	}
}

void UFASkillComponent::SpawnSkill()
{
	FTransform SpawnTransform;
	if(!CurrentSkillExtraData.NeedTargetLocation)
		SpawnTransform = GetOwner()->GetActorTransform();

	AFABaseSkill* SkillActor = GetWorld()->SpawnActorDeferred<AFABaseSkill>(
		CurrentSkillExtraData.Skill, SpawnTransform, GetOwner(), Cast<AFABaseCharacter>(GetOwner())
	);
	

	if(SkillActor)
	{
		SkillActor->SkillNumber = CurrentSkillNumber;
		SkillActor->IsTargettingSkill = CurrentSkillExtraData.NeedTargetLocation;
		if(CurrentSkillExtraData.DecalMat != nullptr)
		{
			SkillActor->DecalComponent->SetDecalMaterial(CurrentSkillExtraData.DecalMat->GetMaterial());
			SkillActor->DecalComponent->SetHiddenInGame(false);
		}
		CurrentSkill = SkillActor;
		UGameplayStatics::FinishSpawningActor(SkillActor, SpawnTransform);
	}
	
}

void UFASkillComponent::PlaySkillMontage()
{
	UAnimInstance* AnimInstance = OwnerCharacter->GetMesh()->GetAnimInstance();
	UAnimMontage* AnimMontage = CurrentSkillExtraData.AnimMontage;
	if(AnimInstance && AnimMontage)
	{
		AnimInstance->Montage_Play(AnimMontage);
		OwnerCharacter->GetController()->StopMovement();
		SetSkillTimer(SkillTimerHandleMap[CurrentSkillNumber], SkillDatas[CurrentSkillNumber].CoolTime);
	}
}

FVector UFASkillComponent::RotateToTarget()
{
	FVector CursorLocation;
	if(OwnerCharacter)
	{
		switch (OwnerCharacter->ControlType)
		{
		case 0:
			{
			AFAPlayerController* PC  = Cast<AFAPlayerController>(OwnerCharacter->GetController());
			CursorLocation = PC->TraceMouseLocation();
			}
			break;
		case 1:
			break;
		case 2:
			break;
		}
	}
	return CursorLocation;
}

void UFASkillComponent::GetRemainCoolTime()
{
	for(auto mapVar : SkillTimerHandleMap)
	{
		if(GetWorld()->GetTimerManager().IsTimerActive(mapVar.Value))
		{
			float time = GetWorld()->GetTimerManager().GetTimerRemaining(mapVar.Value);
			FALOG(Warning, TEXT("%f"), time)
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(mapVar.Value);
		}
	}
}

void UFASkillComponent::SetSkillTimer(FTimerHandle &Handle, float CoolDownTime)
{
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([]()
	{

	}), CoolDownTime, false);
}
