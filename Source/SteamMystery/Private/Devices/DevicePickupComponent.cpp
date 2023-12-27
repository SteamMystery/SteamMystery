// Fill out your copyright notice in the Description page of Project Settings.


#include "Devices/DevicePickupComponent.h"

#include "Game/MainPlayerController.h"
#include "Game/MainPlayerState.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void UDevicePickupComponent::OnInteractCallback_Implementation(const AMainPlayerController* InController)
{
	if (const auto PlayerState = InController->GetPlayerState<AMainPlayerState>())
	{
		PlayerState->AddDevice(DeviceName);
		GetOwner()->Destroy();
		for (int i = 0; i < AMainPlayerState::ActionBarSize; i++)
			if (PlayerState->GetDeviceAt(i).IsNone())
			{
				PlayerState->SetDevice(i, DeviceName);
				return;
			}
	}
}


void UDevicePickupComponent::BeginPlay()
{
	Super::BeginPlay();
	OnInteract.AddUniqueDynamic(this, &ThisClass::OnInteractCallback);
	GetOwner()->Tags.Add(UPlayerInteractionComponent::InteractTag);
}
