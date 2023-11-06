// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveWidget.h"
#include "Blueprint/UserWidget.h"
#include "SavesWidget.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API USavesWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual bool Initialize() override;
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
	TSubclassOf<USaveWidget> SaveWidgetClass = GetClass();
};
