// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FABaseSkill.h"
#include "FASphereShapeSkill.generated.h"

/**
 * 
 */
UCLASS()
class FINDARK_API AFASphereShapeSkill : public AFABaseSkill
{
	GENERATED_BODY()

public:
	AFASphereShapeSkill();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
};
