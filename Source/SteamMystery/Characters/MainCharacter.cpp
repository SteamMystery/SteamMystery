// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "SteamMystery/Weapons/RangedWeapon.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	FirstPersonCamera->SetRelativeLocation(FVector(-10,0,60));
	FirstPersonCamera->bUsePawnControlRotation = true;

	FirstPersonSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	FirstPersonSkeletalMesh->SetupAttachment(FirstPersonCamera);
	FirstPersonSkeletalMesh->SetRelativeLocation(FVector(-30,0,-150));
}


// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);
}



void AMainCharacter::Look(const FVector2D Value)
{
	if (!Controller) return;

	if (Value.X != 0.f)
		AddControllerYawInput(Value.X);

	if (Value.Y != 0.f)
		AddControllerPitchInput(Value.Y);
}

USkeletalMeshComponent* AMainCharacter::GetMainMesh() const
{
	return FirstPersonSkeletalMesh;
}


