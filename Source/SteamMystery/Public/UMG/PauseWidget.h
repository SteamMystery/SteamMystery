// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHUDWidget.h"
#include "PauseWidget.generated.h"

class UGameSaveSubsystem;
class UButton;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UPauseWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void Quit();

	UFUNCTION()
	void Resume();

	UFUNCTION()
	void Saves();

	UFUNCTION()
	void Options();

	UPROPERTY(meta=(BindWidget))
	UButton* ResumeButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* SavesButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* OptionsButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* MainMenuButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitButton = nullptr;
	
	UPROPERTY()
	UGameSaveSubsystem* SaveSubsystem;
};
