// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ItemWidgets/UpgradesWidget.h"

#include "ItemDescriptionWidget.h"
#include "Components/PanelWidget.h"
#include "DataAssets/DataAssetCollections.h"
#include "DataAssets/EquipmentItem.h"
#include "Devices/Device.h"
#include "Game/MainPlayerState.h"
#include "UMG/ItemWidgets/UpgradeDescriptionWidget.h"
#include "UMG/ItemWidgets/UpgradeWidget.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void UUpgradesWidget::UpgradeApplied(const FName InDeviceName, const FName UpgradeName)
{
	PlayerState->AddUpgrade(InDeviceName, UpgradeName);
	Sync();
}

void UUpgradesWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	DescriptionContainer->OnUpgradeApplied.AddUniqueDynamic(this, &ThisClass::UpgradeApplied);
}

void UUpgradesWidget::NativeConstruct()
{
	Super::Super::NativeConstruct();
	PlayerState = GetOwningPlayerState<AMainPlayerState>();
	if (PlayerState)
	{
		FillItems(Devices, GameInstance->GetWeaponsDataTable(), PlayerState->GetDevices(), DeviceWidgetClass);
		for (const auto Element : Devices->GetAllChildren())
			if (const auto ItemWidget = Cast<UItemWidget>(Element))
				ItemWidget->OnClicked.AddUniqueDynamic(this, &ThisClass::ChooseDevice);
	}
	Collections = GameInstance->GetDataAssetCollections();
	Sync();
}

void UUpgradesWidget::Sync()
{
	if (Collections->Devices.Contains(DeviceName))
		if (const auto CDO = Collections->Devices[DeviceName].GetDefaultObject())
			if (const auto DataTable = CDO->GetUpgradesDataTable())
			{
				const auto PlayerUpgrades = PlayerState->GetUpgrades(DeviceName);
				TMap<FName, int32> UpgradesMap;
				for (FName RowName : DataTable->GetRowNames())
					if (!PlayerUpgrades.Contains(RowName))
						UpgradesMap.Add(RowName);
				FillItems(Upgrades, DataTable, UpgradesMap, UpgradeWidgetClass);
				for (const auto Element : Upgrades->GetAllChildren())
					if (const auto ItemWidget = Cast<UUpgradeWidget>(Element))
					{
						ItemWidget->SetDeviceName(DeviceName);
						ItemWidget->OnUpgradeClicked.AddUniqueDynamic(DescriptionContainer,
						                                              &UUpgradeDescriptionWidget::SetUpgrade);
					}
			}
}

void UUpgradesWidget::ChooseDevice(const FDataTableRowHandle& Item, int)
{
	if (const auto Row = Item.GetRow<FEquipmentItem>(GetName()))
	{
		DeviceName = Row->Name;
		Sync();
	}
}
