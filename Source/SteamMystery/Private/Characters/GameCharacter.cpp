// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Characters/GameCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "DataAssets/DataAssetCollections.h"
#include "Game/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SteamMystery/Public/Components/Stats/ElectricityComponent.h"
#include "SteamMystery/Public/Components/Stats/HealthComponent.h"
#include "SteamMystery/Public/Components/InventoryComponent.h"
#include "SteamMystery/Public/Components/Stats/SteamComponent.h"
#include "SteamMystery/Public/Devices/Device.h"
#include "Devices/Weapons/MeleeWeapon.h"
#include "MeleeTraceComponent.h"

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
				if (const auto MainPlayerState = Controller->GetPlayerState<AMainPlayerState>())
				{
					MainPlayerState->SetInputMappingContext(ActionBarInputMapping);
					if (const auto Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
					{
						auto Mappings = ActionBarInputMapping->GetMappings();
						for (int i = 0; i < Mappings.Num(); ++i)
							Input->BindAction(
								Mappings[i].Action, ETriggerEvent::Started,
								MainPlayerState, &AMainPlayerState::Action, i
							);
					}
				}
			}
		}
}

// Sets default values
AGameCharacter::AGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Steam = CreateDefaultSubobject<USteamComponent>(TEXT("Steam"));
	Electricity = CreateDefaultSubobject<UElectricityComponent>(TEXT("Electricity"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	MeleeTraceComponent = CreateDefaultSubobject<UMeleeTraceComponent>(TEXT("MeleeTraceComponent"));
}

void AGameCharacter::HandleDeath()
{
	DetachFromControllerPendingDestroy();
	if (Inventory)
		Tags.Add(UInteractionComponent::InteractTag);
	HandleDeathDelegate.Broadcast();
}

bool AGameCharacter::Attack()
{
	if (MainHand)
		return MainHand->Use();
	return false;
}

void AGameCharacter::AttachDevice(const FName Device)
{
	if (MainHand)
		MainHand->Destroy();
	if (Collections && Collections->Devices.Contains(Device))
	{
		auto Params = FActorSpawnParameters();
		Params.Owner = this;
		MainHand = GetWorld()->SpawnActor<ADevice>(Collections->Devices[Device], Params);
		MainHand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("GripPoint"));
		if(MeleeTraceComponent)
			MeleeTraceComponent->SetWeapon(MainHand);
	}
}

void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (const auto Instance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		Collections = Instance->GetDataAssetCollections();
		AttachDevice(MainHandType);
	}
	if (MeleeTraceComponent)
		MeleeTraceComponent->OnTraceHit.AddUniqueDynamic(this, &ThisClass::HandleMeleeAttack);
}

ADevice* AGameCharacter::GetMainHand() const
{
	return MainHand;
}

void AGameCharacter::HandleMeleeAttack(UMeleeTraceComponent*, AActor* HitActor, const FVector& HitLocation,
                                       const FVector&, FName)
{
	if (const auto MeleeWeapon = Cast<AMeleeWeapon>(MainHand))
		MeleeWeapon->Attack(HitActor, HitLocation);
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
