// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FAEnums.h"
#include "SetCharacterCondition.generated.h"

/**
 * 
 */
UCLASS()
class FINDARK_API USetCharacterCondition : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, meta=(InlineEditConditionToggle))
	bool bIsChangeCondition;
	UPROPERTY(EditAnywhere, meta=(EditCondition="bIsChangeCondition"))
	ECharacterCondition CharacterCondition;

	UPROPERTY(EditAnywhere, meta=(InlineEditConditionToggle))
	bool bIsChangeMovementMode;
	UPROPERTY(EditAnywhere, meta=(EditCondition="bIsChangeMovementMode"))
	TEnumAsByte<EMovementMode> MovementMode = EMovementMode::MOVE_Walking;
};
