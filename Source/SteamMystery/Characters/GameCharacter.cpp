// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

#include "Components/CapsuleComponent.h"
#include "SteamMystery/Components/ElectricityComponent.h"
#include "SteamMystery/Components/HealthComponent.h"
#include "SteamMystery/Components/InventoryComponent.h"
#include "SteamMystery/Components/SteamComponent.h"
#include "SteamMystery/Devices/Device.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Steam = CreateDefaultSubobject<USteamComponent>(TEXT("Steam"));
	Electricity = CreateDefaultSubobject<UElectricityComponent>(TEXT("Electricity"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}


void AGameCharacter::HandleDeath()
{
	// GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	// GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// GetMesh()->SetSimulatePhysics(true);
	DetachFromControllerPendingDestroy();
	if(Inventory)
		Tags.Add("Inventory");
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

UAnimMontage* AGameCharacter::GetAttackAnimMontage() const
{
	return AttackAnimMontage;
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
