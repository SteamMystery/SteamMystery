// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Device.h"

#include "DataAssets/Upgrade.h"
#include "Game/MainPlayerState.h"
#include "Kismet/GameplayStatics.h"
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

bool ADevice::CheckRole() const
{
	return Roles.Contains(ERole::All) || Roles.Contains(PlayerState->GetRole());
}

bool ADevice::Use_Implementation()
{
	const auto OwningCharacter = GetOwner();
	if (bIsOnCooldown || !OwningCharacter || !CheckRole()) return false;

	USteamComponent* SteamComponent = OwningCharacter->GetComponentByClass<USteamComponent>();
	UElectricityComponent* ElectricityComponent = OwningCharacter->GetComponentByClass<UElectricityComponent>();
	const auto Stats = GetStats();
	const auto SteamPrice = Stats.FindRef(EStat::SteamPrice);
	const auto ElectricityPrice = Stats.FindRef(EStat::ElectricityPrice);

	bool bCond = true;

	if (bCond && SteamPrice > 0)
		bCond &= SteamComponent && SteamComponent->CanConsume(SteamPrice);

	if (bCond && ElectricityPrice > 0)
		bCond &= ElectricityComponent && ElectricityComponent->CanConsume(ElectricityPrice);
	
	if (bCond)
	{
		SteamComponent->Consume(SteamPrice);
		ElectricityComponent->Consume(ElectricityPrice);
		
		if (const auto Speed = Stats.FindRef(EStat::Speed); Speed > 0)
		{
			FTimerHandle UnusedTimer;
			bIsOnCooldown = true;
			GetWorld()->GetTimerManager().SetTimer(UnusedTimer, this, &ThisClass::Ready, Speed);
		}
	}

	if (UseSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), UseSound, GetActorLocation(), GetActorRotation());
	
	return bCond;
}

void ADevice::Ready()
{
	bIsOnCooldown = false;
}

void ADevice::BeginPlay()
{
	if (const auto OwningPlayer = Cast<APawn>(GetOwner()))
		if (const auto OwningController = OwningPlayer->GetController())
			PlayerState = OwningController->GetPlayerState<AMainPlayerState>();
	Super::BeginPlay();
	Roles = GetRoles();
}

UDataTable* ADevice::GetUpgradesDataTable() const
{
	return UpgradesDataTable;
}

TMap<EStat, float> ADevice::GetStats() const
{
	if (const auto Item = RowHandle.GetRow<FEquipmentItem>(GetName()))
	{
		if (PlayerState)
			for (const auto Element : PlayerState->GetUpgrades(Item->Name))
				if (const auto Upgrade = UpgradesDataTable->FindRow<FUpgrade>(Element, GetName()))
					Upgrade->Apply(*Item);
		return Item->Stats;
	}
	return TMap<EStat, float>();
}

TArray<ERole> ADevice::GetRoles() const
{
	const auto Item = RowHandle.GetRow<FEquipmentItem>(GetName());
	return Item ? Item->Roles : TArray{ERole::None};
}
