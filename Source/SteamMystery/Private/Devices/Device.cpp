// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Device.h"

#include "DataAssets/Upgrade.h"
#include "Game/MainPlayerState.h"
#include "SteamMystery/Public/Components/Stats/ElectricityComponent.h"
#include "SteamMystery/Public/Components/Stats/SteamComponent.h"
#include "SteamMystery/Public/DataAssets/EquipmentItem.h"

// Sets default values
ADevice::ADevice()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

bool ADevice::Use()
{
	if (bIsRecharging) return false;

	if (const auto Char = GetOwner())
		if (const auto SteamComponent = Char->GetComponentByClass<USteamComponent>())
			if (const auto ElectricityComponent = Char->GetComponentByClass<UElectricityComponent>())
				if (const auto Stats = GetStats();
					SteamComponent->CanConsume(Stats.SteamPrice)
					&& ElectricityComponent->CanConsume(Stats.ElectricityPrice))
				{
					if(Stats.Stats.Contains(EStat::Recharge) && Stats.Stats[EStat::Recharge] > 0)
					{
						FTimerHandle UnusedTimer;
						bIsRecharging = true;
						GetWorld()->GetTimerManager()
								  .SetTimer(UnusedTimer, this, &ThisClass::Ready, Stats.Stats[EStat::Recharge]);
					}
					return SteamComponent->Consume(Stats.SteamPrice)
					&& ElectricityComponent->Consume(Stats.ElectricityPrice);
				}
	return false;
}

void ADevice::Ready()
{
	bIsRecharging = false;
}

void ADevice::BeginPlay()
{
	Super::BeginPlay();
	if (const auto OwningPlayer = Cast<APawn>(GetOwner()))
		if (const auto OwningController = OwningPlayer->GetController())
			PlayerState = OwningController->GetPlayerState<AMainPlayerState>();
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
