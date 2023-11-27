// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainComponentsHUD.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API AMainComponentsHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainComponentsHUD();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBaseWidgetComponent* OptionsWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USavesComponent* SavesWidgetComponent;
};
