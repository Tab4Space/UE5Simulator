// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParser.h"
#include "Misc/FileHelper.h"
#include "JsonObjectConverter.h"

/* Json */
bool UJsonParser::LoadJsonFromFile(const FString& FilePath, FString& JsonStringResult)
{
	if(FFileHelper::LoadFileToString(JsonStringResult, *FilePath))
		return true;
	return false;
}

bool UJsonParser::ParseJsonToStruct(FSettingData* Structure, const FString& JsonString)
{
	if(FJsonObjectConverter::JsonObjectStringToUStruct<FSettingData>(JsonString, Structure, 0, 0))
		return true;
	return false;
}
