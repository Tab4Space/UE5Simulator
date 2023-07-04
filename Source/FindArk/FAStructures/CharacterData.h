#pragma once

#include "SkillData.h"
#include "CharacterData.generated.h"

USTRUCT()
struct FCharacterData
{
	GENERATED_BODY()

	UPROPERTY()
	FString CharacterName;
	UPROPERTY()
	int32 CharacterType;
	UPROPERTY()
	int32 ControlType;
	UPROPERTY()
	float MaxHealth;
	UPROPERTY()
	float MaxMana;
	UPROPERTY()
	float BaseAttackDamage;
	UPROPERTY()
	float BaseArmor;
	UPROPERTY()
	float CriticalProb;
	UPROPERTY()
	bool IsEnemy;
	UPROPERTY()
	TArray<int32> UseSkills;
	UPROPERTY()
	TArray<FSkillData> Skills;
};