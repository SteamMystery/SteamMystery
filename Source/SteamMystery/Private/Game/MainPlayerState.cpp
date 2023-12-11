// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MainPlayerState.h"

#include "InputMappingContext.h"
#include "Characters/GameCharacter.h"
#include "Game/GameSave.h"
#include "Game/GameSaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Quest/QuestManager.h"


void AMainPlayerState::Sync(UGameSave* GameSave)
{
	CurrentSave = GameSave;
}

void AMainPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (const auto SaveSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UGameSaveSubsystem>())
	{
		Sync(SaveSubsystem->GetSave());
		SaveSubsystem->OnSaveLoaded.AddUniqueDynamic(this, &ThisClass::Sync);
	}
	if (const auto Controller = GetOwningController())
		OwningCharacter = Cast<AGameCharacter>(Controller->GetPawn());
}

AMainPlayerState::AMainPlayerState()
{
	QuestManager = CreateDefaultSubobject<UQuestManager>(TEXT("QuestManager"));
}

int AMainPlayerState::GetCoins() const
{
	return CurrentSave->Coins;
}

TArray<FName> AMainPlayerState::GetUpgrades(const FName DeviceName) const
{
	if (CurrentSave->Upgrades.Contains(DeviceName))
		return CurrentSave->Upgrades[DeviceName].Purchased;
	return TArray<FName>();
}

void AMainPlayerState::AddCoins(const int Value) const
{
	CurrentSave->Coins += Value;
}

bool AMainPlayerState::RemoveCoins(const int Value) const
{
	if (CurrentSave->Coins >= Value)
	{
		CurrentSave->Coins -= Value;
		return true;
	}
	return false;
}

TMap<FName, int32> AMainPlayerState::GetItems() const
{
	return CurrentSave->Items;
}

void AMainPlayerState::AddUpgrade(const FName DeviceName, const FName Value) const
{
	if (!CurrentSave->Upgrades.Contains(DeviceName))
		CurrentSave->Upgrades.Add(DeviceName);
	CurrentSave->Upgrades[DeviceName].Purchased.Add(Value);
}

void AMainPlayerState::AddItem(const FName Item, const int Count = 1) const
{
	if (CurrentSave->Items.Contains(Item))
		CurrentSave->Items[Item] += Count;
	else
		CurrentSave->Items.Add(Item, Count);
}

bool AMainPlayerState::RemoveItem(const FName Item, const int Count = 1) const
{
	if (CurrentSave->Items.Contains(Item) && CurrentSave->Items[Item] >= Count)
	{
		CurrentSave->Items[Item] -= Count;
		if (CurrentSave->Items[Item] == 0)
			CurrentSave->Items.Remove(Item);
		return true;
	}
	return false;
}


TMap<FName, int32> AMainPlayerState::GetDevices() const
{
	return CurrentSave->Devices;
}

void AMainPlayerState::AddDevice(const FName Item) const
{
	CurrentSave->Devices.Add(Item);
}

void AMainPlayerState::RemoveDevice(const FName Item) const
{
	CurrentSave->Devices.Remove(Item);
}

FName AMainPlayerState::GetDeviceAt(const int32 Index) const
{
	if (CurrentSave && Index >= 0 && Index < CurrentSave->ActionBar.Num())
		return CurrentSave->ActionBar[Index];
	return FName("");
}

void AMainPlayerState::SetDevice(const int32 Index, const FName Item)
{
	if (CurrentSave && Index >= 0 && Index < CurrentSave->ActionBar.Num())
		CurrentSave->ActionBar[Index] = Item;
	ActionBarChanged.Broadcast();
}

FText AMainPlayerState::GetKeyAt(const int32 Index)
{
	if (Index >= 0 && Index < ActionBarKeys.Num())
		return ActionBarKeys[Index];
	return FText::GetEmpty();
}

void AMainPlayerState::SetInputMappingContext(UInputMappingContext* InputMappingContext)
{
	ActionBarInputMapping = InputMappingContext;
	if (ActionBarInputMapping)
		for (auto Mapping : ActionBarInputMapping->GetMappings())
			ActionBarKeys.Add(Mapping.Key.GetDisplayName());
}

void AMainPlayerState::Action(const FInputActionValue&, const int Index)
{
	OwningCharacter->AttachDevice(GetDeviceAt(Index));
}
