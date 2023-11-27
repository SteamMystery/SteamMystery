// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Characters/GameCharacter.h"

#include "SteamMystery/Public/Components/Stats/ElectricityComponent.h"
#include "SteamMystery/Public/Components/Stats/HealthComponent.h"
#include "SteamMystery/Public/Components/InventoryComponent.h"
#include "SteamMystery/Public/Components/Stats/SteamComponent.h"
#include "SteamMystery/Public/Devices/Device.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Steam = CreateDefaultSubobject<USteamComponent>(TEXT("Steam"));
	Electricity = CreateDefaultSubobject<UElectricityComponent>(TEXT("Electricity"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void AGameCharacter::HandleDeath()
{
	DetachFromControllerPendingDestroy();
	if(Inventory)
		Tags.Add("Inventory");
	HandleDeathDelegate.Broadcast();
	
}

USkeletalMeshComponent* AGameCharacter::GetMainMesh() const
{
	return GetMesh();
}


bool AGameCharacter::Attack()
{
	if (MainHand)
		return MainHand->Use();
	return false;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (MainHandClass)
	{
		MainHand = GetWorld()->SpawnActor<ADevice>(MainHandClass);
		MainHand->AttachToComponent(GetMainMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));
		MainHand->SetOwner(this);
		bHasRifle = true;
	}
}

ADevice* AGameCharacter::GetMainHand() const
{
	return MainHand;
}


void AGameCharacter::Look(const FVector2D Value)
{
	if (!Controller) return;

	if (Value.X != 0.f)
		AddControllerYawInput(Value.X);

	if (Value.Y != 0.f)
		AddControllerPitchInput(Value.Y);
}


void AGameCharacter::Move(const FVector2D Value)
{
	if (!Controller) return;

	// Right/Left direction
	if (Value.X != 0.f)
		AddMovementInput(GetActorRightVector(), Value.X);

	// Forward/Backward direction
	if (Value.Y != 0.f)
		AddMovementInput(GetActorForwardVector(), Value.Y);
}
