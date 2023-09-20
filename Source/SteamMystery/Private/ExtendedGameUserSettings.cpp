// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendedGameUserSettings.h"


UExtendedGameUserSettings::UExtendedGameUserSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MasterVolume = 1.0f;
	AmbientVolume = 0.8f;
	DialogVolume = 0.65f;
	EffectVolume = 0.75f;
	MusicVolume = 0.9f;
}

void UExtendedGameUserSettings::SetAudioCategoryVolume(EVolumeType VolumeCategory, float NewVolume)
{
	switch (VolumeCategory)
	{
	case EVolumeType::EVT_Master:
		MasterVolume = NewVolume;
		break;
	case EVolumeType::EVT_Ambient:
		AmbientVolume = NewVolume;
		break;
	case EVolumeType::EVT_Dialog:
		DialogVolume = NewVolume;
		break;
	case EVolumeType::EVT_Effect:
		EffectVolume = NewVolume;
		break;
	case EVolumeType::EVT_Music:
		MusicVolume = NewVolume;
		break;
	}
}
