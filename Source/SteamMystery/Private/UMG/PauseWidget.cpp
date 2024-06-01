// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppMemberFunctionMayBeConst
#include "SteamMystery/Public/UMG/PauseWidget.h"

#include "Components/Button.h"
#include "Game/GameSaveSubsystem.h"
#include "SteamMystery/Public/Components/UMG/PauseComponent.h"
#include "SteamMystery/Public/Components/UMG/SavesComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SteamMystery/Public/HUDs/PlayerHUD.h"


void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (QuitButton)
		QuitButton->OnClicked.AddDynamic(this, &UPauseWidget::Quit);
	if (OptionsButton)
		OptionsButton->OnClicked.AddDynamic(this, &UPauseWidget::Options);
	if (SavesButton)
		SavesButton->OnClicked.AddDynamic(this, &UPauseWidget::Saves);
	if (ResumeButton)
		ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::Resume);
}

void UPauseWidget::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}

void UPauseWidget::Resume()
{
	HUD->PauseComponent->Close(1);
}

void UPauseWidget::Saves()
{
// 	UE_LOG(LogTemp, Warning, TEXT("%p"), HUD->SavesWidgetComponent->GetWidget())
// 	HUD->SavesWidgetComponent->ShowAsSaveable(1);
	SaveSubsystem->SaveGame("Saves");
}

void UPauseWidget::Options()
{
	HUD->OptionsWidgetComponent->Show(1);
}
