// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UActionBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Sync();
	
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UPanelWidget* Skills;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class USkillSlotWidget> SkillSlotWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AMainPlayerState* PlayerState;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UDataTable* DataTable;
};
