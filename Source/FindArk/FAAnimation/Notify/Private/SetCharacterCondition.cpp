// Fill out your copyright notice in the Description page of Project Settings.


#include "SetCharacterCondition.h"
#include "FABaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void USetCharacterCondition::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	AFABaseCharacter* OwnerCharacter = Cast<AFABaseCharacter>(MeshComp->GetOwner());
	
	if(OwnerCharacter)
	{
		if(bIsChangeCondition)
			OwnerCharacter->CharacterCondition = CharacterCondition;
		if(bIsChangeMovementMode)
			OwnerCharacter->GetCharacterMovement()->SetMovementMode(MovementMode);
	}
}
