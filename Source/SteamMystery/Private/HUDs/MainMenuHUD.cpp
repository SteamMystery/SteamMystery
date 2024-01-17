// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/HUDs/MainMenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "SteamMystery/Public/Components/UMG/BaseWidgetComponent.h"
#include "SteamMystery/Public/Components/UMG/SavesComponent.h"
#include "SteamMystery/Public/UMG/MainMenuWidget.h"


void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	if (const auto OwningPlayerController = GetOwningPlayerController())
	{
		if (BackgroundWidgetClass)
			CreateWidget(OwningPlayerController, BackgroundWidgetClass)->AddToViewport(0);
		if (MainMenuWidgetClass)
		{
			MainMenuWidget = CreateWidget<UMainMenuWidget>(OwningPlayerController, MainMenuWidgetClass);
			OptionsWidgetComponent->SetParentWidget(MainMenuWidget);
			SavesWidgetComponent->SetParentWidget(MainMenuWidget);
			MainMenuWidget->AddToViewport(1);
		}
		OwningPlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(OwningPlayerController);
	}
}

AMainMenuHUD::AMainMenuHUD()
{
	NewGameWidgetComponent = CreateDefaultSubobject<UBaseWidgetComponent>(TEXT("New Game"));
}
