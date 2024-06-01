// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppMemberFunctionMayBeConst

#include "SteamMystery/Public/UMG/SaveWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Game/GameSaveSubsystem.h"
#include "Game/MainPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Quest/QuestManager.h"
#include "SteamMystery/Public/Game/GameSave.h"


void USaveWidget::NativeConstruct()
{
	Super::NativeConstruct();
	QuestManager = GetOwningPlayer()->GetPlayerState<AMainPlayerState>()->QuestManager;
	SaveSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UGameSaveSubsystem>();

	if (SaveButton)
		SaveButton->OnClicked.AddUniqueDynamic(this, &USaveWidget::Save);

	if (LoadButton)
		LoadButton->OnClicked.AddUniqueDynamic(this, &USaveWidget::Load);

	if (DeleteButton)
		DeleteButton->OnClicked.AddUniqueDynamic(this, &USaveWidget::Delete);
}

void USaveWidget::Sync()
{
	const bool bDoesSaveGameExist = UGameplayStatics::DoesSaveGameExist(SlotName, 0);
	if (bDoesSaveGameExist)
	{
		if (const auto Save = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)))
			if (SaveTimeTextBlock)
				SaveTimeTextBlock->SetText(FText::AsDateTime(Save->Time));
	}
	else
		SaveTimeTextBlock->SetText(FText::GetEmpty());
	SetLoadable(bDoesSaveGameExist);
}

void USaveWidget::SetName(const FString Value)
{
	SlotName = Value;
	if (SaveNameTextBlock)
		SaveNameTextBlock->SetText(FText::FromString(Value));
	Sync();
}

void USaveWidget::Save()
{
	QuestManager->SaveQuestData(SlotName);
	SaveSubsystem->SaveGame(SlotName);
	Sync();
}

void USaveWidget::Load()
{
	SaveSubsystem->LoadGame(SlotName);
	QuestManager->ROS_LoadFromSaveGame_Implementation(SlotName);
	QuestManager->QuestRepInventoryUpdated.Broadcast();
	Sync();
}

void USaveWidget::Delete()
{
	UGameplayStatics::DeleteGameInSlot(SlotName, 0);
	Sync();
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
