// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SteamMysteryEditorTarget : TargetRules
{
	public SteamMysteryEditorTarget(TargetInfo target) : base(target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new[] { "SteamMystery" } );
	}
}
