// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SteamMystery/HealthComponent.h"
#include "SteamMystery/Weapons/RangedWeapon.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
		GetCharacterMovement()->JumpZVelocity = 700.f;
    	GetCharacterMovement()->AirControl = 0.35f;
    	GetCharacterMovement()->MaxWalkSpeed = 500.f;
    	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
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

void AGameCharacter::HandleDeath()
{
	if (RootComponent)
		RootComponent->DestroyComponent();
	GetMesh()->SetSimulatePhysics(true);
}

void AGameCharacter::RangedAttack() const
{
	if (const auto x = Cast<ARangedWeapon>(Weapon))
		x->Fire();
}

USkeletalMeshComponent* AGameCharacter::GetMainMesh() const
{
	return GetMesh();
}
