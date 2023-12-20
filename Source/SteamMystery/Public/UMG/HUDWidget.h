// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UProgressBar;
class UHealthBarBase;
class UElectricityComponent;
class USteamComponent;
class UHealthComponent;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY()
	UHealthComponent* HealthComponent;
	UPROPERTY()
	USteamComponent* SteamComponent;
	UPROPERTY()
	UElectricityComponent* ElectricityComponent;

	UPROPERTY(meta=(BindWidget))
	UHealthBarBase* HealthBar;
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* Steam;
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* Electricity;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Monologue;

public:
	void SetMonologue(const FText& InText) const;
};
