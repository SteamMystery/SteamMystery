// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Characters/GameCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EquipmentComponent.h"
#include "InputMappingContext.h"
#include "SteamMystery/Public/Components/Stats/ElectricityComponent.h"
#include "SteamMystery/Public/Components/Stats/HealthComponent.h"
#include "SteamMystery/Public/Components/InventoryComponent.h"
#include "SteamMystery/Public/Components/Stats/SteamComponent.h"
#include "SteamMystery/Public/Devices/Device.h"

void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (const auto PlayerController = Cast<APlayerController>(GetController()))
		if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PlayerController->GetLocalPlayer()
		))
		{
			Subsystem->ClearAllMappings();
			if (DefaultInputMapping)
				Subsystem->AddMappingContext(DefaultInputMapping, 0);
			if (ActionBarInputMapping)
			{
				Subsystem->AddMappingContext(ActionBarInputMapping, 1);
				if (EquipmentComponent)
				{
					EquipmentComponent->SetInputMapping(ActionBarInputMapping);
					if (const auto Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
					{
						auto Mappings = ActionBarInputMapping->GetMappings();
						for (int i = 0; i < Mappings.Num(); ++i)
							Input->BindAction(
								Mappings[i].Action, ETriggerEvent::Started,
								EquipmentComponent, &UEquipmentComponent::Action, i
							);
					}
				}
			}
		}
}

// Sets default values
AGameCharacter::AGameCharacter()
{
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Steam = CreateDefaultSubobject<USteamComponent>(TEXT("Steam"));
	Electricity = CreateDefaultSubobject<UElectricityComponent>(TEXT("Electricity"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment"));
}

void AGameCharacter::HandleDeath()
{
	DetachFromControllerPendingDestroy();
	if (Inventory)
		Tags.Add("Inventory");
	HandleDeathDelegate.Broadcast();
}


bool AGameCharacter::Attack()
{
	if (MainHand)
		return MainHand->Use();
	return false;
}

void AGameCharacter::AttachDevice(const TSubclassOf<ADevice> Class)
{
	if(MainHand)
		MainHand->Destroy();
	if(Class)
	{
		MainHand = GetWorld()->SpawnActor<ADevice>(Class);
		MainHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));
		MainHand->SetOwner(this);
	}
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (MainHandClass)
		AttachDevice(MainHandClass);
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
