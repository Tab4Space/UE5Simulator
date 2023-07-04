// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "FAEnums.h"
#include "FABaseSkill.generated.h"

class UDecalComponent;
class AFAPlayerController;
class AFABaseCharacter;
class UMaterial;

UCLASS()
class FINDARK_API AFABaseSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFABaseSkill();
	virtual void Tick(float DeltaTime) override;
	void SetupActorInputComponent(UInputComponent* myInputComponent);
	void SetTargetLocation();
	UFUNCTION()
	virtual void OnBeginDamage(ETraceType TraceType, FVector Modifier);
	virtual void OnEndDamage();
	virtual void ApplySkillDamage();
	UFUNCTION()
	void SkillDestroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool TraceSphere(FVector OriginLocation, FVector Modifier);
	bool TraceDonut(FVector OriginLocation, FVector Modifier);
	bool TraceeCone(FVector OriginLocation, FVector Modifier);
	bool TraceRectangle(FVector OriginLocation, FVector Modifier);
	bool TraceCylinder(FVector OriginLocation, FVector Modifier);


public:
	UPROPERTY(EditAnywhere)
	UDecalComponent* DecalComponent;
	UPROPERTY()
	AFABaseCharacter* FAOwnerCharacter;
	UPROPERTY()
	AFAPlayerController* FAController;
	UPROPERTY(VisibleAnywhere)
	int32 SkillNumber;
	UPROPERTY(VisibleAnywhere)
	bool IsTargettingSkill;
	UPROPERTY(VisibleAnywhere)
	bool IsSetTargetLocation;
	UPROPERTY(VisibleAnywhere)
	FVector SkillTargetLocation;
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*>TraceResultActors;
	UPROPERTY(VisibleAnywhere)
	UMaterial* DecalMatrial;

};
