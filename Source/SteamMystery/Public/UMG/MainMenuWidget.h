// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void Quit();
	UFUNCTION()
	void Options();
	UFUNCTION()
	void NewGame();
	UFUNCTION()
	void LoadGame();

	UPROPERTY()
	class AMainMenuHUD* MainMenuHUD;

	UPROPERTY(meta=(BindWidget))
	UButton* NewGameButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* LoadGameButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* OptionsButton = nullptr;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitButton = nullptr;

	UPROPERTY(EditAnywhere)
	UWorld* NewGameLevel = nullptr;
};
