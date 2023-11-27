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
	
	virtual bool Initialize() override;

	virtual void NativeOnInitialized() override;
public:
	UFUNCTION(BlueprintCallable)
	void SetSaveable(bool bIsSaveable) const;
	
private:
	inline static int MaxSavesNumber = 8;
	
	UFUNCTION(BlueprintPure)
	static int GetMaxSavesNumber();

	
	UPROPERTY(EditAnywhere)
	TMap<int, UGameSave*> Saves;

	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* SaveSlots;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<USaveWidget> SaveWidgetClass;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	class AMainComponentsHUD* MainComponentsHUD;
};
