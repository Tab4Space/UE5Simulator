/* Message Structure for IPC */

#pragma once

#include "Message.generated.h"

USTRUCT()
struct FMessage
{
	GENERATED_BODY()

	UPROPERTY()
	int32 ID;

	UPROPERTY()
	FVector location;
};

USTRUCT()
struct FActionMessage
{
	GENERATED_BODY()

	UPROPERTY()
	FVector2D MouseXY;
	UPROPERTY()
	int32 SkillNumber;
	UPROPERTY()
	FVector SkillTargetLoc;
	UPROPERTY()
	int32 ItemNumber;
	UPROPERTY()
	FVector ItemTargetLoc;
};

USTRUCT()
struct FStateMessage
{
	GENERATED_BODY()

	UPROPERTY()
	int32 ID;

	UPROPERTY()
	FVector Location;
};

USTRUCT()
struct FImageMessage
{
	GENERATED_BODY()

	UPROPERTY()
	int32 ID;

	UPROPERTY()
	uint32 Location;
};