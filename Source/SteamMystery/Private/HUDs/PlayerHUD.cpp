// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/HUDs/PlayerHUD.h"

#include "Blueprint/UserWidget.h"
#include "SteamMystery/Public/Components/UMG/PauseComponent.h"
#include "SteamMystery/Public/Components/UMG/SavesComponent.h"
#include "SteamMystery/Public/UMG/HUDWidget.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	if (const auto OwningPlayerController = GetOwningPlayerController())
		if (HUDWidgetClass)
		{
			HUDWidget = CreateWidget<UHUDWidget>(OwningPlayerController, HUDWidgetClass);
			//PauseComponent->SetParentWidget(HUDWidget);
			if (const auto Widget = PauseComponent->GetWidget())
			{
				SavesWidgetComponent->SetParentWidget(Widget);
				OptionsWidgetComponent->SetParentWidget(Widget);
			}
			HUDWidget->AddToViewport(0);
		}
}

APlayerHUD::APlayerHUD()
{
	PauseComponent = CreateDefaultSubobject<UPauseComponent>(TEXT("Pause"));
	InventoryComponent = CreateDefaultSubobject<UPauseComponent>(TEXT("Inventory"));
	EquipmentComponent = CreateDefaultSubobject<UPauseComponent>(TEXT("Equipment"));
}
