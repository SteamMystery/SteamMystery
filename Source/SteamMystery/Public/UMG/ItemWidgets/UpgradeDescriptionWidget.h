// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDescriptionWidget.h"
#include "DataAssets/Upgrade.h"
#include "Game/MainPlayerState.h"
#include "UpgradeDescriptionWidget.generated.h"

class UMaterialWidget;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpgradeApplied, FName, DeviceName, FName, UpgradeName);
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UUpgradeDescriptionWidget : public UItemDescriptionWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void ApplyUpgrade();
	virtual void NativeConstruct() override;
	virtual void Sync() const override;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UPanelWidget* Materials;

	FName DeviceName;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMaterialWidget> MaterialWidgetClass;

	UPROPERTY()
	AMainPlayerState* PlayerState;

public:
	UFUNCTION(BlueprintCallable)
	void SetUpgrade(const FName InDeviceName, const FDataTableRowHandle& InUpgrade);
	
	UPROPERTY(BlueprintAssignable)
	FOnUpgradeApplied OnUpgradeApplied;
};
