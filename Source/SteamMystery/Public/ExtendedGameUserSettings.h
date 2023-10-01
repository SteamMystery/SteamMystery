// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ExtendedGameUserSettings.generated.h"

UENUM(BlueprintType)
enum class EVolumeType : uint8
{
	EVT_Master UMETA(DisplayName="Master Volume"),
	EVT_Ambient UMETA(DisplayName="Ambient Volume"),
	EVT_Dialog UMETA(DisplayName="Dialog Volume"),
	EVT_Effect UMETA(DisplayName="Effect Volume"),
	EVT_Music UMETA(DisplayName="Music Volume"),
};

/**
 * 
 */
UCLASS(config = Settings, configdonotcheckdefaults)
class STEAMMYSTERY_API UExtendedGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
public:
	/** 
	* Sets the volume value for the given category for audio output.
	* @Param	VolumeCategory	Category to set volume for.
	* @Param	NewVolume		The new value for the volume.
	*/
	UFUNCTION(BlueprintCallable)
	void SetAudioCategoryVolume(EVolumeType VolumeCategory, float NewVolume);

	/** Gets the Master Volume value. */
	UFUNCTION(BlueprintPure)
	float GetMasterVolume() const { return MasterVolume; }

	/** Gets the Ambient Volume value. */
	UFUNCTION(BlueprintPure)
	float GetAmbientVolume() const { return AmbientVolume; }

	/** Gets the Dialog Volume value. */
	UFUNCTION(BlueprintPure)
	float GetDialogVolume() const { return DialogVolume; }

	/** Gets the Effect Volume value. */
	UFUNCTION(BlueprintPure)
	float GetEffectVolume() const { return EffectVolume; }

	/** Gets the Music Volume value. */
	UFUNCTION(BlueprintPure)
	float GetMusicVolume() const { return MusicVolume; }

	UFUNCTION(BlueprintCallable)
	static UExtendedGameUserSettings* GetExtendedGameUserSettings()
	{
		return Cast<UExtendedGameUserSettings>(UGameUserSettings::GetGameUserSettings());
	}

protected:
	/** Master volume value */
	UPROPERTY(config)
	float MasterVolume;

	/** Ambient volume value */
	UPROPERTY(config)
	float AmbientVolume;

	/** Dialog volume value */
	UPROPERTY(config)
	float DialogVolume;

	/** Effect volume value */
	UPROPERTY(config)
	float EffectVolume;

	/** Music volume value */
	UPROPERTY(config)
	float MusicVolume;
};
