// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Components/CapsuleComponent.h"
#include "SteamMystery/Components/HealthComponent.h"
#include "SteamMystery/Weapons/RangedWeapon.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponClass)
	{
		Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
		Weapon->AttachToComponent(GetMainMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));
		Weapon->SetOwner(this);
		bHasRifle = true;
	}
}


void AMainCharacter::Move(const FVector2D Value)
{
	if (!Controller) return;

	// Right/Left direction
	if (Value.X != 0.f)
		AddMovementInput(GetActorRightVector(), Value.X);

	// Forward/Backward direction
	if (Value.Y != 0.f)
		AddMovementInput(GetActorForwardVector(), Value.Y);
}

void AMainCharacter::HandleDeath()
{
	DetachFromControllerPendingDestroy();
	GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetSimulatePhysics(true);
}

void AMainCharacter::Attack() const
{
	Weapon->Attack();
}

USkeletalMeshComponent* AMainCharacter::GetMainMesh() const
{
	return GetMesh();
}
