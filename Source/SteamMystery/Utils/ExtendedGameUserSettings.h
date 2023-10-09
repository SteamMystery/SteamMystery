// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "ExtendedGameUserSettings.generated.h"

USTRUCT(BlueprintType)
struct FSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 Textures;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Reflection;
	
	UPROPERTY(BlueprintReadWrite)
	int32 GlobalIllumination;
	
	UPROPERTY(BlueprintReadWrite)
	int32 ViewDistance;
	
	UPROPERTY(BlueprintReadWrite)
	int32 PostProcessing;
	
	UPROPERTY(BlueprintReadWrite)
	int32 AntiAliasing;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Shading;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Shadows;
	
	UPROPERTY(BlueprintReadWrite)
	int32 VisualEffects;
	
	UPROPERTY(BlueprintReadWrite)
	int32 Foliage;
	
	UPROPERTY(BlueprintReadWrite)
	FIntPoint ScreenResolution;
	
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EWindowMode::Type> InFullScreenMode;
	
	UPROPERTY(BlueprintReadWrite)
	bool VSync;
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
UCLASS(config = Settings, configdonotcheckdefaults)
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
	
	UPROPERTY(config)
	float MasterVolume;

	UPROPERTY(config)
	float AmbientVolume;

	UPROPERTY(config)
	float DialogVolume;

	UPROPERTY(config)
	float EffectVolume;

	UPROPERTY(config)
	float MusicVolume;
};
