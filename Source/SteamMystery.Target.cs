// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SteamMysteryTarget : TargetRules
{
	public SteamMysteryTarget(TargetInfo target) : base(target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new[] { "SteamMystery" } );
	}
}
