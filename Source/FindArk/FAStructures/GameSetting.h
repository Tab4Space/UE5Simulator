// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimData.h"
#include "CharacterData.h"
#include "GameSetting.generated.h"


USTRUCT()
struct FSettingData
{
	GENERATED_BODY()

	UPROPERTY()
	FSimData Simulator;
	UPROPERTY()
	TArray<FCharacterData> Characters;
};
