// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FindArk : ModuleRules
{
	public FindArk(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "FindArk.h";
		
		PrivateIncludePaths.AddRange(new [] {
			"FindArk/FAAnimation/AnimInstance/Public",
			"FindArk/FAAnimation/Notify/Public",
			"FindArk/FAAnimation/NotifyState/Public",
			"FindArk/FACharacters/Public",
			"FindArk/FAComponents/Public",
			"FindArk/FAControllers/Public",
			"FindArk/FACore/Public",
			"FindArk/FASkills/Base/Public",
			"FindArk/FASkills/SorceressSkills/Public",
			"FindArk/FAStructures",
			"FindArk/Utils/Json/Public",
			
		});
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore", "Json", "JsonUtilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
