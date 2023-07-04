// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"


DECLARE_LOG_CATEGORY_EXTERN(FALOG, Log, All);

#define FALOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define FALOG_S(Verbosity) UE_LOG(FALOG, Verbosity, TEXT("%s"), *FALOG_CALLINFO)
#define FALOG(Verbosity, Format, ...) UE_LOG(FALOG, Verbosity, TEXT("%s %s"), *FALOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))


#define LOADING_SEMAPHORE	TEXT("Global\\FINDARK_LOADING_SEMAPHORE")
#define UE_SERVER_SEMAPHORE	TEXT("Global\\FINDARK_UESERVER_SEMAPHORE")
#define PY_CLIENT_SEMAPHORE	TEXT("Global\\FINDARK_PYCLIENT_SEMAPHORE")
#define SHARED_MEMORY_NAME	TEXT("FINDARK_SHAREDMEMORY4")