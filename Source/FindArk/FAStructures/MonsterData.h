#pragma once

#include "MonsterData.generated.h"

USTRUCT()
struct FMonsterData
{
	GENERATED_BODY()

	UPROPERTY()
	FString MonsterType;
	UPROPERTY()
	float BaseHealth;
	UPROPERTY()
	float BaseAttackDamage;
};