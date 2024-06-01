// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SavesWidget.generated.h"

class UGameSave;
class USaveWidget;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API USavesWidget : public UUserWidget
{
	GENERATED_BODY()

	void Fill();
	
	virtual void NativePreConstruct() override;

	virtual void NativeOnInitialized() override;

public:
	static constexpr int MaxSavesNumber = 8;

	UFUNCTION(BlueprintCallable)
	void SetSaveable(bool bIsSaveable) const;

private:

	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* SaveSlots;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USaveWidget> SaveWidgetClass;

protected:
	UPROPERTY(BlueprintReadOnly)
	class AMainComponentsHUD* MainComponentsHUD;
};
