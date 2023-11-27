// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/UMG/SavesWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/VerticalBox.h"
#include "SteamMystery/Public/Game/GameSave.h"
#include "SteamMystery/Public/HUDs/MainComponentsHUD.h"
#include "SteamMystery/Public/UMG/SaveWidget.h"

int USavesWidget::GetMaxSavesNumber()
{
	return MaxSavesNumber;
}

bool USavesWidget::Initialize()
{
	const auto b = Super::Initialize();
	if (b)
		for (auto i = 1; i <= MaxSavesNumber; i++)
		{
			const auto SlotName = FString::FormatAsNumber(i);
			const auto Widget = Cast<USaveWidget>(CreateWidget(this, SaveWidgetClass, *SlotName));
			Widget->SetName(FString::FromInt(i));
			if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
			{
				const auto Save = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
				Saves.Add(i, Save);
				Widget->SetSaveTime(FText::AsDateTime(Save->Time));
				Widget->SetLoadable(true);
			}
			else
				Widget->SetLoadable(false);
			SaveSlots->AddChild(Widget);
		}
	return b;
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
