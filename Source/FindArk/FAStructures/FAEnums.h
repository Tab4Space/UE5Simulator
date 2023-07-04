#pragma once
#include "FAEnums.generated.h"

UENUM()
enum class EConnectType : uint8
{
	E_SharedMemory		UMETA(DisplayName = "Shared Memory"),
	E_TCP				UMETA(DisplayName = "TCP Socket")
};

UENUM()
enum class EPlayMode : uint8
{
	E_Develop			UMETA(DisplayName = "Shared Memory"),
	E_HumanControl		UMETA(DisplayName = "Human Control"),
	E_DeepLearning		UMETA(DisplayName = "TCP Socket")
};

UENUM()
enum class ETraceType : uint8
{
	E_TraceSphere			UMETA(DisplayName = "Trace Sphere"),
	E_TraceCone				UMETA(DisplayName = "Trace Cone"),
	E_TraceDonut			UMETA(DisplayName = "Trace Donut"),
	E_TraceRectangle		UMETA(DisplayName = "Trace Rectangle"),
	E_TraceCylinder			UMETA(DisplayName = "Trace Cylinder")
};

UENUM()
enum class ECharacterCondition : uint8
{
	E_Idle					UMETA(DisplayName = "Idle"),
	E_Moving				UMETA(DisplayName = "Moving"),
	E_Attacking				UMETA(DisplayName = "Attacking"),
	E_ExecutingSkill		UMETA(DisplayName = "Executing Skill"),
	E_Dead					UMETA(DisplayName = "Dead")
};