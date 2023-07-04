// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAEnums.h"
#include "Message.h"
#include "GameFramework/Character.h"
#include "FABaseCharacter.generated.h"

class UInputComponent;
class UCameraComponent;
class USpringArmComponent;
class UFAStatComponent;
class UFASkillComponent;
class AFAPlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIsMovingDelegate);


UCLASS()
class FINDARK_API AFABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFABaseCharacter();

	void AllocateBuffer();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	

	unsigned char* ActionBuffer;
	unsigned char* StateBuffer;

public:
	UPROPERTY(VisibleAnywhere)
	UFAStatComponent* StatComponent;

	UPROPERTY(VisibleAnywhere)
	UFASkillComponent* SkillComponent;
	
	UPROPERTY(VisibleAnywhere)
	int32 PlayerId;
	
	UPROPERTY(VisibleAnywhere)
	FString CharName;

	UPROPERTY(VisibleAnywhere)
	uint8 CharacterTpe;

	UPROPERTY(VisibleAnywhere)
	uint8 ControlType;

	UPROPERTY(VisibleAnywhere)
	bool bIsEnemy;

	UPROPERTY(VisibleAnywhere)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	TArray<int32> UsableSkillNumbers;

	UPROPERTY();
	FVector CurrentLocation;
	UPROPERTY()
	bool bActing;
	UPROPERTY()
	bool IsMoving;
	
	FActionMessage	ActionMessage;
	FStateMessage	StateMessage;

	UPROPERTY(BlueprintAssignable)
	FIsMovingDelegate OnIsMoveingDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterCondition CharacterCondition = ECharacterCondition::E_Idle;

public:
	void InitCharacter(int32 PlayerIndex);
	void ExecSkill(int32 SkillNumber);
	void GetState();

	UFUNCTION()
	void SetCharacterMoving();

public:
	FORCEINLINE uint8 GetControlType() const { return ControlType; }

};
