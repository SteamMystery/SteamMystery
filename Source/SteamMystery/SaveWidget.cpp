// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveWidget.h"

#include "GameSave.h"
#include "SteamMysteryGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


bool USaveWidget::Initialize()
{
	Instance = Cast<USteamMysteryGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	return Super::Initialize();
}

void USaveWidget::SetName(const FString Value)
{
	SlotName = Value;
	if (SaveNameTextBlock)
		SaveNameTextBlock->SetText(FText::FromString(Value));
}

void USaveWidget::SetSaveTime(const FText Value) const
{
	if (SaveTimeTextBlock)
		SaveTimeTextBlock->SetText(Value);
}

void USaveWidget::SetGameTime(const FText Value) const
{
	if (GameTimeTextBlock)
		GameTimeTextBlock->SetText(Value);
}

void USaveWidget::Save()
{
	UGameplayStatics::SaveGameToSlot(Instance->GetSave(), SlotName, 0);
}

void USaveWidget::Load()
{
	UGameplayStatics::LoadGameFromSlot(SlotName, 0);
}

void USaveWidget::Delete()
{
	UGameplayStatics::DeleteGameInSlot(SlotName, 0);
}

void USaveWidget::SetSaveable(const bool bIsSaveable) const
{
	if (SaveButton)
		SaveButton->SetVisibility(bIsSaveable ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USaveWidget::SetLoadable(const bool bIsLoadable) const
{
	const auto EVisibility = bIsLoadable ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	if (LoadButton)
		LoadButton->SetVisibility(EVisibility);
	if (DeleteButton)
		DeleteButton->SetVisibility(EVisibility);
}

TSharedRef<SWidget> USaveWidget::RebuildWidget()
{
	const auto Widget = Super::RebuildWidget();

	if (SaveButton)
		SaveButton->OnClicked.AddDynamic(this, &USaveWidget::Save);

	if (LoadButton)
		LoadButton->OnClicked.AddDynamic(this, &USaveWidget::Load);

	if (DeleteButton)
		DeleteButton->OnClicked.AddDynamic(this, &USaveWidget::Delete);

	return Widget;
}
