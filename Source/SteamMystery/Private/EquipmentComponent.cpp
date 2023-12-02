// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"

#include "InputMappingContext.h"
#include "Characters/GameCharacter.h"
#include "Devices/Device.h"

UEquipmentComponent::UEquipmentComponent()
{
	ActionBar.SetNum(ActionBarSize);
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningCharacter = Cast<AGameCharacter>(GetOwner());
}

inline TArray<TSubclassOf<ADevice>> UEquipmentComponent::GetItems() const
{
	return Items;
}

void UEquipmentComponent::SetInputMapping(UInputMappingContext* Value)
{
	InputMapping = Value;
	if (InputMapping)
		for (auto Mapping : InputMapping->GetMappings())
			ActionBarKeys.Add(Mapping.Key.GetDisplayName());
}

void UEquipmentComponent::Action(const FInputActionValue&, const int Index)
{
	UE_LOG(LogTemp, Warning, TEXT("Action"));
	OwningCharacter->AttachDevice(GetDeviceAt(Index));
}

TSubclassOf<ADevice> UEquipmentComponent::GetDeviceAt(const int32 Index)
{
	if (Index >= 0 && Index < ActionBar.Num())
		return ActionBar[Index];
	return nullptr;
}

FText UEquipmentComponent::GetKeyAt(const int32 Index)
{
	if (Index >= 0 && Index < ActionBarKeys.Num())
		return ActionBarKeys[Index];
	return FText::GetEmpty();
}

void UEquipmentComponent::SetAction(const int32 Index, const TSubclassOf<ADevice> Item)
{
	if (Index >= 0 && Index < ActionBar.Num())
		ActionBar[Index] = Item;
	ActionBarChanged.Broadcast();
}
