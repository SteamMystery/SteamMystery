// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Game/MainPlayerController.h"

void AMainPlayerController::SetPlayerEnabledState(const bool bPlayerEnabled)
{
	if (bPlayerEnabled)
		GetPawn()->EnableInput(this);
	else
		GetPawn()->DisableInput(this);
	bShowMouseCursor = bPlayerEnabled;
	
}
