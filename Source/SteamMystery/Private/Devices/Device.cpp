// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Device.h"

#include "Characters/GameCharacter.h"
#include "DataAssets/Upgrade.h"
#include "Game/MainPlayerController.h"
#include "SteamMystery/Public/Components/Stats/ElectricityComponent.h"
#include "SteamMystery/Public/Components/Stats/SteamComponent.h"
#include "SteamMystery/Public/DataAssets/EquipmentItem.h"

// Sets default values
ADevice::ADevice()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

bool ADevice::Use()
{
	const auto Char = GetOwner();
	const auto SteamComponent = Char->GetComponentByClass<USteamComponent>();
	const auto ElectricityComponent = Char->GetComponentByClass<UElectricityComponent>();

	if (const auto Stats = GetStats(); SteamComponent->CanConsume(Stats.SteamPrice) && ElectricityComponent->CanConsume(
		Stats.ElectricityPrice))
		return SteamComponent->Consume(Stats.SteamPrice) && ElectricityComponent->Consume(Stats.ElectricityPrice);
	return false;
}

void ADevice::BeginPlay()
{
	Super::BeginPlay();
	if (const auto OwningPlayer = Cast<APawn>(GetOwner()))
	{
		if (const auto OwningController = OwningPlayer->GetController())
			PlayerState = OwningController->GetPlayerState<AMainPlayerState>();
		else
			UE_LOG(LogTemp, Warning, TEXT("OwningController"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("OwningPlayer"));
}


UStaticMeshComponent* ADevice::GetMesh() const
{
	return Mesh;
}

UDataTable* ADevice::GetUpgradesDataTable() const
{
	return UpgradesDataTable;
}

FEquipmentItem ADevice::GetStats() const
{
	if (const auto Row = RowHandle.GetRow<FEquipmentItem>(GetName()))
	{
		auto Item = *Row;
		if (PlayerState)
		{
			for (const auto Element : PlayerState->GetUpgrades(Item.Name))
				if (const auto Upgrade = UpgradesDataTable->FindRow<FUpgrade>(Element, GetName()))
					Upgrade->Apply(Item);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("PlayerState"));
		return Item;
	}
	return FEquipmentItem();
}
