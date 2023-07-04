#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillData.h"
#include "TimerManager.h"
#include "FASkillComponent.generated.h"

class AFABaseCharacter;
class UAnimInstance;
class UAnimMontage;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FINDARK_API UFASkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFASkillComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InitSkillData();
	void ActivateSkill(int32 SkillNumber);
	void SpawnSkill();
	void PlaySkillMontage();
	FVector RotateToTarget();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	AFABaseCharacter* OwnerCharacter;
	UPROPERTY(VisibleInstanceOnly)
	TMap<int32, FSkillData> SkillDatas;		//<skillnumber, fskilldata>
	UPROPERTY(EditDefaultsOnly)
	UDataTable* SkillExtrDataTable;
	UPROPERTY(VisibleInstanceOnly)
	FSkillExtraData CurrentSkillExtraData;
	UPROPERTY(VisibleInstanceOnly)
	int32 CurrentSkillNumber;
	UPROPERTY(VisibleInstanceOnly)
	AFABaseSkill* CurrentSkill = nullptr;
	
	UPROPERTY()
	FTimerHandle SkillTimerManagerHandle;
	UPROPERTY()
	TMap<int32, FTimerHandle> SkillTimerHandleMap;
	
	void GetRemainCoolTime();
	void SetSkillTimer(FTimerHandle &Handle, float CoolDownTime);

public:
	FORCEINLINE UDataTable* GetSkillExtraDataTable() const { return SkillExtrDataTable; }
};
