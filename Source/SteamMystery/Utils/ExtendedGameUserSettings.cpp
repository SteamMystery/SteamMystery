// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendedGameUserSettings.h"

void UExtendedGameUserSettings::SetAudioCategoryVolume(const EVolumeType VolumeCategory, const float Value)
{
	switch (VolumeCategory)
	{
	case EVolumeType::Master: MasterVolume = Value;
		break;
	case EVolumeType::Ambient: AmbientVolume = Value;
		break;
	case EVolumeType::Dialog: DialogVolume = Value;
		break;
	case EVolumeType::Effect: EffectVolume = Value;
		break;
	case EVolumeType::Music: MusicVolume = Value;
		break;
	}
}

float UExtendedGameUserSettings::GetAudioCategoryVolume(const EVolumeType VolumeCategory) const
{
	switch (VolumeCategory)
	{
	case EVolumeType::Ambient: return AmbientVolume;
	case EVolumeType::Dialog: return DialogVolume;
	case EVolumeType::Effect: return EffectVolume;
	case EVolumeType::Music: return MusicVolume;
	default: return MasterVolume;
	}
}

UExtendedGameUserSettings* UExtendedGameUserSettings::GetExtendedGameUserSettings()
{
	return Cast<UExtendedGameUserSettings>(GetGameUserSettings());
}

void UExtendedGameUserSettings::SetAll(const FSettings& Settings)
{
	SetTextureQuality(Settings.Textures);
	SetReflectionQuality(Settings.Reflection);
	SetGlobalIlluminationQuality(Settings.GlobalIllumination);
	SetViewDistanceQuality(Settings.ViewDistance);
	SetPostProcessingQuality(Settings.PostProcessing);
	SetAntiAliasingQuality(Settings.AntiAliasing);
	SetShadingQuality(Settings.Shading);
	SetShadowQuality(Settings.Shadows);
	SetVisualEffectQuality(Settings.VisualEffects);
	SetFoliageQuality(Settings.Foliage);
	SetScreenResolution(Settings.ScreenResolution);
	SetFullscreenMode(Settings.InFullScreenMode);
	SetVSyncEnabled(Settings.VSync);
}
