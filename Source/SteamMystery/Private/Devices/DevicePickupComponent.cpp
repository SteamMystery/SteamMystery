// Fill out your copyright notice in the Description page of Project Settings.


#include "Devices/DevicePickupComponent.h"

#include "DataAssets/EquipmentItem.h"
#include "Game/GameSave.h"
#include "Game/GameSaveSubsystem.h"
#include "Game/MainPlayerController.h"
#include "Game/MainPlayerState.h"
#include "Kismet/GameplayStatics.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void UDevicePickupComponent::OnInteractCallback_Implementation(const AMainPlayerController* InController)
{
	if (const auto PlayerState = InController->GetPlayerState<AMainPlayerState>())
	{
		PlayerState->AddDevice(Device.RowName);
		GetOwner()->Destroy();
		for (int i = 0; i < AMainPlayerState::ActionBarSize; i++)
			if (PlayerState->GetDeviceAt(i).IsNone())
			{
				PlayerState->SetDevice(i, Device.RowName);
				return;
			}
	}
}


void UDevicePickupComponent::BeginPlay()
{
	if (const auto SaveSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UGameSaveSubsystem>())
		if (const auto Save = SaveSubsystem->GetSave())
			if (const auto Row = Device.GetRow<FEquipmentItem>(GetName()))
				if (Row->Roles.Contains(Save->GetRole()))
				{
					OnInteract.AddUniqueDynamic(this, &ThisClass::OnInteractCallback);
					GetOwner()->Tags.Add(UPlayerInteractionComponent::InteractTag);
				}
				else
					GetOwner()->Destroy();
	Super::BeginPlay();
}
