// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Game/MainPlayerController.h"

#include "Components/InteractionComponent.h"


AMainPlayerController::AMainPlayerController()
{
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction"));
}

void AMainPlayerController::SetPlayerEnabledState(const bool bPlayerEnabled)
{
	if (bPlayerEnabled)
		GetPawn()->EnableInput(this);
	else
		GetPawn()->DisableInput(this);
	bShowMouseCursor = bPlayerEnabled;
}
