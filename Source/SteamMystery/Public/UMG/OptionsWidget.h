// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsWidget.generated.h"

class UWidgetSwitcher;
class UButton;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
protected:

	UPROPERTY(meta=(BindWidget))
	UButton* SoundButton;

	UPROPERTY(meta=(BindWidget))
	UButton* GraphicsButton;

	UPROPERTY(meta=(BindWidget))
	UButton* ControlsButton;

	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(BlueprintReadOnly)
	TArray<UButton*> TabButtons;
	
	UPROPERTY(BlueprintReadOnly)
	class AMainComponentsHUD* MainComponentsHUD;

	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable)
	void SetActiveWidget(int32 Index);
};
