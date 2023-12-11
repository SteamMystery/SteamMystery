// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/UMG/SavesWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/VerticalBox.h"
#include "SteamMystery/Public/Game/GameSave.h"
#include "SteamMystery/Public/HUDs/MainComponentsHUD.h"
#include "SteamMystery/Public/UMG/SaveWidget.h"

void USavesWidget::Fill()
{
	for (auto i = 1; i <= MaxSavesNumber; i++)
	{
		const auto SlotName = FString::FormatAsNumber(i);
		if(const auto Widget = Cast<USaveWidget>(CreateWidget(this, SaveWidgetClass)))
		{
			Widget->SetName(SlotName);
			SaveSlots->AddChild(Widget);
		}
	}
}

void USavesWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	Fill();
}

void USavesWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MainComponentsHUD = Cast<AMainComponentsHUD>(GetOwningPlayer()->GetHUD());
}

void USavesWidget::SetSaveable(const bool bIsSaveable) const
{
	for(const auto Child : SaveSlots->GetAllChildren())
		Cast<USaveWidget>(Child)->SetSaveable(bIsSaveable);
}
