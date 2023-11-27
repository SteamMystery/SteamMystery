// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainComponentsHUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API AMainMenuHUD : public AMainComponentsHUD
{
	GENERATED_BODY()

	UPROPERTY()
	UUserWidget* BackgroundWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> BackgroundWidgetClass;

	UPROPERTY()
	class UMainMenuWidget* MainMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;


protected:
	virtual void BeginPlay() override;
};
