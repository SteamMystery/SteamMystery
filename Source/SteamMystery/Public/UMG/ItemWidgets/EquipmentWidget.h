// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemCollectionWidget.h"
#include "EquipmentWidget.generated.h"

class UDeviceWidget;
class UTextBlock;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UEquipmentWidget : public UItemCollectionWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void Sync() override;
	
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* Devices;
	
	UPROPERTY(meta=(BindWidget))
	class UItemDescriptionWidget* DescriptionContainer;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemWidget> DeviceWidgetClass;

};
