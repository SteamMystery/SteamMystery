// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Game/MainPlayerController.h"

#include "Components/PlayerInteractionComponent.h"


AMainPlayerController::AMainPlayerController()
{
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("Interaction"));
}

void AMainPlayerController::SetPlayerEnabledState(const bool bPlayerEnabled)
{
	if (bPlayerEnabled)
		GetPawn()->EnableInput(this);
	else
		GetPawn()->DisableInput(this);
	bShowMouseCursor = bPlayerEnabled;
}
