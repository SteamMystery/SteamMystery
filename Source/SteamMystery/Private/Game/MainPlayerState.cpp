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

ERole AMainPlayerState::GetRole() const
{
	return CurrentSave->GetRole();
}

TArray<FName> AMainPlayerState::GetUpgrades(const FName DeviceName) const
{
	return CurrentSave->Upgrades.FindRef(DeviceName).Purchased;
}

TMap<FName, int32> AMainPlayerState::GetItems() const
{
	return CurrentSave->Items;
}

void AMainPlayerState::AddUpgrade(const FName DeviceName, const FName Value) const
{
	auto& [Purchased] = CurrentSave->Upgrades.FindOrAdd(DeviceName);
	Purchased.Add(Value);
}

void AMainPlayerState::AddItem(const FName InItem, const int InCount = 1) const
{
	if (const auto Count = CurrentSave->Items.Find(InItem))
		*Count += InCount;
	else
		CurrentSave->Items.Add(InItem, InCount);
}

bool AMainPlayerState::RemoveItem(const FName InItem, const int InCount = 1) const
{
	if (const auto Count = CurrentSave->Items.Find(InItem); *Count >= InCount)
	{
		*Count -= InCount;
		if (*Count == 0)
			CurrentSave->Items.Remove(InItem);
		return true;
	}
	return false;
}

int32 AMainPlayerState::GetMaxCount(const FName InItem, const int InCount = 1) const
{
	if (const auto Count = CurrentSave->Items.Find(InItem))
		return *Count > InCount ? InCount : *Count;
	return 0;
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
	return CurrentSave && Index >= 0 && Index < CurrentSave->ActionBar.Num()
	? CurrentSave->ActionBar[Index]
	: NAME_None;
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

// ReSharper disable once CppMemberFunctionMayBeConst
void AMainPlayerState::Action(const FInputActionValue&, const int Index)
{
	OwningCharacter->AttachDevice(GetDeviceAt(Index));
}
