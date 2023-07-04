// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "FABaseSkill.h"
#include "Animation/AnimMontage.h"
#include "SkillData.generated.h"

USTRUCT()
struct FSkillData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleInstanceOnly)
	int32 SkillNumber;
	UPROPERTY(VisibleInstanceOnly)
	FString SkillName = "";
	UPROPERTY(VisibleInstanceOnly)
	float DamageFactor;
	UPROPERTY(VisibleInstanceOnly)
	float CoolTime;
	UPROPERTY(VisibleInstanceOnly)
	float CostMana;
};

USTRUCT()
struct FSkillExtraData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFABaseSkill> Skill;
	UPROPERTY(EditAnywhere)
	UTexture2D* SkillIcon;
	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimMontage;
	UPROPERTY(EditAnywhere)
	UMaterialInstance* DecalMat;
	UPROPERTY(EditAnywhere)
	bool IsRotateToCursor;
	UPROPERTY(EditAnywhere, meta=(EditCondition="IsRotateToCursor"))
	bool NeedTargetLocation;
	UPROPERTY(EditAnywhere)
	FVector LocationModifier;
	UPROPERTY(EditAnywhere)
	FVector SizeModifier;
	UPROPERTY(VisibleDefaultsOnly)
	FTimerHandle CoolDownTimer;
};