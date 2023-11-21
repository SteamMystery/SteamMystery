// Fill out your copyright notice in the Description page of Project Settings.


#include "Device.h"

#include "SteamMystery/Characters/GameCharacter.h"
#include "SteamMystery/Components/ElectricityComponent.h"
#include "SteamMystery/Components/SteamComponent.h"

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
	
	if (SteamComponent->CanConsume(SteamPrice) && ElectricityComponent->CanConsume(ElectricityPrice))
		return SteamComponent->Consume(SteamPrice) && ElectricityComponent->Consume(ElectricityPrice);
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
