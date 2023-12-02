// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/BaseHUDWidget.h"
#include "EquipmentWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UEquipmentWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UEquipmentComponent* EquipmentComponent;
	
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* Items;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Description;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDeviceWidget> ItemWidgetClass;
	
};
