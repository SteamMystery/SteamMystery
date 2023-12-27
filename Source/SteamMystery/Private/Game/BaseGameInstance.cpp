// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Game/BaseGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "SteamMystery/Public/Game/ExtendedGameUserSettings.h"

void UBaseGameInstance::Init()
{
	Super::Init();
	UExtendedGameUserSettings::GetExtendedGameUserSettings()->LoadSettings(true);
}

UDataTable* UBaseGameInstance::GetItemsDataTable() const
{
	return ItemsDataTable;
}

UDataTable* UBaseGameInstance::GetUpgradesDataTable() const
{
	return UpgradesDataTable;
}

UDataTable* UBaseGameInstance::GetWeaponsDataTable() const
{
	return WeaponsDataTable;
}

UDataAssetCollections* UBaseGameInstance::GetDataAssetCollections() const
{
	return DataAssetCollections;
}

void UBaseGameInstance::BeginDestroy()
{
	Super::BeginDestroy();
	UGameplayStatics::DeleteGameInSlot("PlayerQuestData", 0);
}
