// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Characters/PlayerCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SteamMystery/Public/Components/InteractionComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	 SpringArm->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("FP_Camera"));
	 SpringArm->TargetArmLength = 0;
	 FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	 FirstPersonCamera->SetupAttachment(SpringArm);
	 //FirstPersonCamera->SetRelativeLocation(FVector(-10,0,60));
	 FirstPersonCamera->bUsePawnControlRotation = true;
	 //
	 // FirstPersonSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	 // FirstPersonSkeletalMesh->SetupAttachment(FirstPersonCamera);
	 // FirstPersonSkeletalMesh->SetRelativeLocation(FVector(-30,0,-150));
	
	 Grabber = CreateDefaultSubobject<UInteractionComponent>(TEXT("Grabber"));
	 Grabber->SetupAttachment(FirstPersonCamera);
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->HideBoneByName(TEXT("weapon_l"), PBO_None);
}

// // Called to bind functionality to input
// void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	//Super::SetupPlayerInputComponent(PlayerInputComponent);
// 	if(InputMapping)
// 	{
// 		const APlayerController* PlayerController = Cast<APlayerController>(GetController());
// 		const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
// 			PlayerController->GetLocalPlayer());
// 		Subsystem->ClearAllMappings();
// 		Subsystem->AddMappingContext(InputMapping, 0);
// 	}
// }


// USkeletalMeshComponent* APlayerCharacter::GetMainMesh() const
// {
// 	return FirstPersonSkeletalMesh;
// }
