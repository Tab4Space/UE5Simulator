// Fill out your copyright notice in the Description page of Project Settings.


#include "FAGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "JsonParser.h"

UFAGameInstance::UFAGameInstance()
{
	PlayMode = 0;
	SpeedRatio = 1.0;
	InGameThread = false;
	RecordPlay = false;
	UseSkillVFX = false;
	DrawSkillDebug = false;
	MapName = "";
	PlayTimeLimit = 600.0;
}

void UFAGameInstance::Init()
{
	if(InitializeGameSetting())
		FALOG(Warning, TEXT("Load Game Setting from Json File"))
	else
		FALOG(Fatal, TEXT("Failed loading game setting from Json File"))
	Super::Init();
	
}

bool UFAGameInstance::InitializeGameSetting()
{
	if(UJsonParser::LoadJsonFromFile(UKismetSystemLibrary::GetPlatformUserDir()+"FindArkSetting.json", JsonString))
	{
		FALOG(Warning, TEXT("%s"), *JsonString)
		if(UJsonParser::ParseJsonToStruct(&SettingData, JsonString))
		{
			PlayMode		= SettingData.Simulator.PlayMode;
			ConnectType		= SettingData.Simulator.ConnectType;
			SpeedRatio		= SettingData.Simulator.SpeedRatio;
			InGameThread	= SettingData.Simulator.InGameThread;
			RecordPlay		= SettingData.Simulator.RecordPlay;
			UseSkillVFX		= SettingData.Simulator.UseSkillVFX;
			DrawSkillDebug	= SettingData.Simulator.DrawSkillDebug;
			MapName			= SettingData.Simulator.MapName;
			PlayTimeLimit	= SettingData.Simulator.PlayTimeLimit;
			return true;
		}
	}
	return false;
}
