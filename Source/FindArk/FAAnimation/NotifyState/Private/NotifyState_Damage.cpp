// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_Damage.h"
#include "FABaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "FASkillComponent.h"

void UNotifyState_Damage::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	AFABaseCharacter* OwnerCharacter = Cast<AFABaseCharacter>(MeshComp->GetOwner());
	if(OwnerCharacter)
	{
		UFASkillComponent* SkillComponent = OwnerCharacter->FindComponentByClass<UFASkillComponent>();
		if(SkillComponent)
			SkillComponent->CurrentSkill->OnBeginDamage(TraceType, Modifier);
	}
}

void UNotifyState_Damage::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AFABaseCharacter* OwnerCharacter = Cast<AFABaseCharacter>(MeshComp->GetOwner());
	if(OwnerCharacter)
	{
		UFASkillComponent* SkillComponent = OwnerCharacter->FindComponentByClass<UFASkillComponent>();
		SkillComponent->CurrentSkill->OnEndDamage();
	}
	
	/*
	AFABaseCharacter* Owner = Cast<AFABaseCharacter>(MeshComp->GetOwner());
	if(Owner != nullptr)
	{
		UFASkillComponent* SkillComponent = Owner->FindComponentByClass<UFASkillComponent>();
		if(SkillComponent != nullptr)
			FALOG(Warning, TEXT("%s"), *SkillComponent->GetName())
	}
	*/
}
