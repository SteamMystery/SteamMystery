// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveWidget.generated.h"

class UGameSave;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API USaveWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
	void Sync();

public:
	
	UFUNCTION(BlueprintCallable)
	void SetName(const FString Value);

	UFUNCTION()
	void Save();
	
	UFUNCTION()
	void Load();
	
	UFUNCTION()
	void Delete();

	UFUNCTION(BlueprintCallable)
	void SetSaveable(bool bIsSaveable) const;
	
	UFUNCTION(BlueprintCallable)
	void SetLoadable(const bool bIsLoadable) const;
	
private:

	FString SlotName;
	UPROPERTY()
	class UQuestManager* QuestManager;

	UPROPERTY()
	class UGameSaveSubsystem* SaveSubsystem;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SaveNameTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SaveTimeTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* GameTimeTextBlock;

	UPROPERTY(meta=(BindWidget))
	UButton* SaveButton;
	
	UPROPERTY(meta=(BindWidget))
	UButton* LoadButton;
	
	UPROPERTY(meta=(BindWidget))
	UButton* DeleteButton;
};
