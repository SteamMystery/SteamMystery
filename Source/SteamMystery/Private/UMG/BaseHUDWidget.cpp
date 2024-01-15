// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/UMG/BaseHUDWidget.h"
#include "SteamMystery/Public/HUDs/PlayerHUD.h"

void UBaseHUDWidget::NativeOnInitialized()
{
	HUD = Cast<APlayerHUD>(GetOwningPlayer()->GetHUD());	
	Super::NativeOnInitialized();
}
