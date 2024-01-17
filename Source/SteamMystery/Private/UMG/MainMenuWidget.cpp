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
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::Quit);
	if(OptionsButton)
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::Options);
	if(NewGameButton)
		NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::NewGame);
	if(LoadGameButton)
		LoadGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::LoadGame);
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
	MainMenuHUD->NewGameWidgetComponent->Show(1);
}

void UMainMenuWidget::LoadGame()
{
	MainMenuHUD->SavesWidgetComponent->Show(1);
}