// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppMemberFunctionMayBeConst
#include "SteamMystery/Public/UMG/MainMenuWidget.h"


#include "SteamMystery/Public/Components/UMG/BaseWidgetComponent.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SteamMystery/Public/Components/UMG/SavesComponent.h"
#include "SteamMystery/Public/HUDs/MainMenuHUD.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MainMenuHUD = Cast<AMainMenuHUD>(GetOwningPlayer()->GetHUD());
	if(QuitButton)
		QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::Quit);
	if(OptionsButton)
		OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::Options);
	// if(NewGameButton)
	// 	NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::NewGame);
	if(LoadGameButton)
		LoadGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::LoadGame);
}

void UMainMenuWidget::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(),EQuitPreference::Quit, false);
}

void UMainMenuWidget::Options()
{
	MainMenuHUD->OptionsWidgetComponent->Show(1);
}

void UMainMenuWidget::NewGame()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NewGameLevel);
}

void UMainMenuWidget::LoadGame()
{
	MainMenuHUD->SavesWidgetComponent->Show(1);
}