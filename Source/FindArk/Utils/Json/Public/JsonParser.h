// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameSetting.h"
#include "JsonParser.generated.h"


UCLASS()
class FINDARK_API UJsonParser : public UObject
{
	GENERATED_BODY()

public:
	/* Json */
	static bool LoadJsonFromFile(const FString& FilePath, FString& JsonStringResult);
	static bool ParseJsonToStruct(FSettingData* Structure, const FString& JsonString);
	
};
