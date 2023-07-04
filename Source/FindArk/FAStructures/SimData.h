#pragma once

#include "SimData.generated.h"

USTRUCT()
struct FSimData
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 PlayMode;
	UPROPERTY()
	int32 ConnectType;
	UPROPERTY()
	float SpeedRatio;
	UPROPERTY()
	bool InGameThread;
	UPROPERTY()
	bool RecordPlay;
	UPROPERTY()
	bool UseSkillVFX;
	UPROPERTY()
	bool DrawSkillDebug;
	UPROPERTY()
	FString MapName;
	UPROPERTY()
	float PlayTimeLimit;
};