// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FAStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINDARK_API UFAStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFAStatComponent();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InitStatData();

public:
	UPROPERTY(VisibleAnywhere)
	float MaxHealth;
	UPROPERTY(VisibleAnywhere)
	float MaxMana;
	UPROPERTY(VisibleAnywhere)
	float BaseAttackDamage;
	UPROPERTY(VisibleAnywhere)
	float BaseArmor;
	UPROPERTY(VisibleAnywhere)
	float CriticalProb;
};
