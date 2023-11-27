// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Device.h"
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

	if (const auto Stats = GetStats(); SteamComponent->CanConsume(Stats->SteamPrice) && ElectricityComponent->CanConsume(Stats->ElectricityPrice))
		return SteamComponent->Consume(Stats->SteamPrice) && ElectricityComponent->Consume(Stats->ElectricityPrice);
	return false;
}

FString ADevice::GetDeviceName() const
{
	return DeviceName;
}

void ADevice::BeginPlay()
{
	Super::BeginPlay();
}

UStaticMeshComponent* ADevice::GetMesh() const
{
	return Mesh;
}