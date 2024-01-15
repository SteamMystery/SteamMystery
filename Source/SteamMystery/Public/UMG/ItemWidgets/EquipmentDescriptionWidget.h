// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDescriptionWidget.h"
#include "EquipmentDescriptionWidget.generated.h"

class UStatWidget;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UEquipmentDescriptionWidget : public UItemDescriptionWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* Stats;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UStatWidget> StatWidgetClass;

	virtual void Sync() const override;
};
