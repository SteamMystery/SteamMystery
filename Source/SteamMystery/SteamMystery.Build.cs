// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SteamMystery : ModuleRules
{
	public SteamMystery(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp20;
	
		PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "GameplayTasks", "QuestEditor", "QuestEditorDev", "GameplayTags"});

		PrivateDependencyModuleNames.AddRange(new[] { "EnhancedInput", "NavigationSystem"  });

		PrivateDependencyModuleNames.AddRange(new[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
