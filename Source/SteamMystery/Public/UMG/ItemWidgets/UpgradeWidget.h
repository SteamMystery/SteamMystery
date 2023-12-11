// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/EquipmentItem.h"
#include "UMG/ItemWidgets/BaseItemWidget.h"
#include "UpgradeWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpgradeClickedEvent, FName, Name, const FDataTableRowHandle&, Item);

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UUpgradeWidget : public UBaseItemWidget
{
	GENERATED_BODY()

protected:
	virtual FReply
	NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	FName DeviceName;

public:
	FOnUpgradeClickedEvent OnUpgradeClicked;

	FDataTableRowHandle RowHandle;

	void SetDeviceName(FName InDeviceName);
};
