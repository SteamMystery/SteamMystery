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

	virtual void NativeConstruct() override;

	UFUNCTION()
	void Sync();
protected:

	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UPanelWidget* Skills;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class USkillSlotWidget> SkillSlotWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UEquipmentComponent* EquipmentComponent;
	
};
