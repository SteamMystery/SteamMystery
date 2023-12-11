// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemCollectionWidget.h"
#include "DataAssets/EquipmentItem.h"
#include "Game/MainPlayerState.h"
#include "UpgradesWidget.generated.h"

class UUpgradeWidget;
class UDeviceWidget;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UUpgradesWidget : public UItemCollectionWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void UpgradeApplied(FName InDeviceName, FName UpgradeName);
	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void Sync() override;
	
	UFUNCTION()
	void ChooseDevice(const FDataTableRowHandle& Item, int Count);
	
	UPROPERTY(meta=(BindWidget))
	class UUpgradeDescriptionWidget* DescriptionContainer;
	
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* Devices;
	
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* Upgrades;
		
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemWidget> DeviceWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUpgradeWidget> UpgradeWidgetClass;
	
	UPROPERTY()
	AMainPlayerState* PlayerState;
	
	UPROPERTY()
	UDataAssetCollections* Collections;
	FName DeviceName;
};
