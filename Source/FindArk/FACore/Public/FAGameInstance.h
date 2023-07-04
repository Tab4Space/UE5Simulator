#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameSetting.h"
#include "FAGameInstance.generated.h"


UCLASS()
class FINDARK_API UFAGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFAGameInstance();
	virtual void Init() override;
	bool InitializeGameSetting();

private:
	UPROPERTY()
	FString				JsonString;
	UPROPERTY()
	FSettingData		SettingData;
	UPROPERTY()
	int32				PlayMode;
	UPROPERTY()
	int32				ConnectType;
	UPROPERTY()
	float				SpeedRatio;
	UPROPERTY()
	bool				InGameThread;
	UPROPERTY()
	bool				RecordPlay;
	UPROPERTY()
	bool				UseSkillVFX;
	UPROPERTY()
	bool				DrawSkillDebug;
	UPROPERTY()
	FString				MapName;
	UPROPERTY()
	float				PlayTimeLimit;


public:
	FORCEINLINE FSettingData	GetSettingData() const		{return SettingData; }
	FORCEINLINE int32			GetPlayMode() const			{ return PlayMode;}
	FORCEINLINE int32			GetConnectType() const		{ return ConnectType; }
	FORCEINLINE float			GetSpeedRatio() const		{ return SpeedRatio; }
	FORCEINLINE bool			GetInGameThread() const		{ return InGameThread; }
	FORCEINLINE bool			GetRecordPlay() const		{ return RecordPlay; }
	FORCEINLINE bool			GetUseSkillVFX() const		{ return UseSkillVFX; }
	FORCEINLINE bool			GetDrawSkillDebug() const	{ return DrawSkillDebug; }
	FORCEINLINE FString			GetMapName() const			{ return MapName; }
	FORCEINLINE float			GetPlayTimeLimit() const	{ return PlayTimeLimit;}
};
