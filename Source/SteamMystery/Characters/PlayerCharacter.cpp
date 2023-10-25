// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
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
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);
}


USkeletalMeshComponent* APlayerCharacter::GetMainMesh() const
{
	return FirstPersonSkeletalMesh;
}


