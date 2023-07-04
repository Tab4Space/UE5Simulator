// Fill out your copyright notice in the Description page of Project Settings.


#include "FASphereShapeSkill.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/DecalComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"

AFASphereShapeSkill::AFASphereShapeSkill()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DecalMat(TEXT("/Game/Decals/Materials/MI_Telegraph_Circle"));
	if(DecalMat.Succeeded())
		DecalComponent->SetDecalMaterial(DecalMat.Object->GetMaterial());
}

void AFASphereShapeSkill::BeginPlay()
{
	Super::BeginPlay();
}

void AFASphereShapeSkill::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
