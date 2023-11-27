// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ExtendedGameUserSettings.generated.h"
#define GAME_USER_SETTINGS_VERSION 8
USTRUCT(BlueprintType)
struct FSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 Textures = 0;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Reflection = 0;
	
	UPROPERTY(BlueprintReadWrite)
	int32 GlobalIllumination = 0;
	
	UPROPERTY(BlueprintReadWrite)
	int32 ViewDistance = 0;
	
	UPROPERTY(BlueprintReadWrite)
	int32 PostProcessing = 0;
	
	UPROPERTY(BlueprintReadWrite)
	int32 AntiAliasing = 0;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Shading = 0;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Shadows = 0;
	
	UPROPERTY(BlueprintReadWrite)
	int32 VisualEffects = 0;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Foliage = 0;
	
	UPROPERTY(BlueprintReadWrite)
	FIntPoint ScreenResolution = FIntPoint();
	
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EWindowMode::Type> InFullScreenMode = EWindowMode::Windowed;
	
	UPROPERTY(BlueprintReadWrite)
	bool VSync = false;
};

UENUM(BlueprintType)
enum class EVolumeType : uint8
{
	Master UMETA(DisplayName="Master Volume"),
	Ambient UMETA(DisplayName="Ambient Volume"),
	Dialog UMETA(DisplayName="Dialog Volume"),
	Effect UMETA(DisplayName="Effect Volume"),
	Music UMETA(DisplayName="Music Volume"),
};

/**
 * 
 */
UCLASS(config = HGameUserSettings, configdonotcheckdefaults)
class STEAMMYSTERY_API UExtendedGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void SetAudioCategoryVolume(EVolumeType VolumeCategory, float Value);
	
	UFUNCTION(BlueprintPure)
	float GetAudioCategoryVolume(EVolumeType VolumeCategory) const;
	
	UFUNCTION(BlueprintCallable)
	static UExtendedGameUserSettings* GetExtendedGameUserSettings();

	UFUNCTION(BlueprintCallable)
	void SetAll(const FSettings& Settings);

	UFUNCTION(BlueprintPure)
	FSettings GetAll() const;

protected:
	virtual bool IsVersionValid() override;
	virtual void UpdateVersion() override;
	
	UPROPERTY(Config)
	float MasterVolume;

	UPROPERTY(Config)
	float AmbientVolume;

	UPROPERTY(Config)
	float DialogVolume;

	UPROPERTY(Config)
	float EffectVolume;

	UPROPERTY(Config)
	float MusicVolume;
};
