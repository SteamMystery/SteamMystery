// Fill out your copyright notice in the Description page of Project Settings.


#include "Device.h"

#include "SteamMystery/Components/ElectricityComponent.h"
#include "SteamMystery/Components/SteamComponent.h"

// Sets default values
ADevice::ADevice()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void ADevice::Use() const
{
	const auto Char = GetOwner();
	const auto SteamComponent = Char->GetComponentByClass<USteamComponent>();
	SteamComponent->Consume(SteamPrice);
	const auto ElectricityComponent = Char->GetComponentByClass<UElectricityComponent>();
	ElectricityComponent->Consume(ElectricityPrice);
}

USkeletalMeshComponent* ADevice::GetMesh() const
{
	return Mesh;
}

