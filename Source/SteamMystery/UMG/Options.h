// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "SteamMystery/Utils/ExtendedGameUserSettings.h"
#include "GameFramework/GameUserSettings.h"

#include "Options.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UOptions : public UUserWidget
{
	GENERATED_BODY()
	
private:
	// UPROPERTY()
	// UExtendedGameUserSettings* Settings = UExtendedGameUserSettings::GetExtendedGameUserSettings();
	//
	UPROPERTY(meta=(BindWidget))
	UButton* Cancel;

	UPROPERTY(meta=(BindWidget))
	UButton* Save;

	UPROPERTY(meta=(BindWidget))
	UButton* Sound;

	UPROPERTY(meta=(BindWidget))
	UButton* Graphics;

	UPROPERTY(meta=(BindWidget))
	UButton* Controls;

	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY()
	TArray<UButton*> TabButtons = TArray{Sound, Graphics, Controls};

	UPROPERTY(EditAnywhere)
	USoundMix* SoundMix;
	
	virtual bool Initialize() override;

	void OnSave();

	void OnCancel();

	void OnSoundClicked();

	void OnGraphicsClicked();

	void OnControlsClicked();
	
	void SetActiveWidget(int32 Index);
};
