// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

int UInventoryComponent::GetCoins() const
{
	return Coins;
}

void UInventoryComponent::AddCoins(const int Value)
{
	Coins += Value;
}

bool UInventoryComponent::RemoveCoins(const int Value)
{
	if (Coins >= Value)
	{
		Coins -= Value;
		return true;
	}
	return false;
}

TMap<UItem*, int32> UInventoryComponent::GetItems() const
{
	return Items;
}

void UInventoryComponent::AddItem(UItem* Item, const int Count = 1)
{
	UE_LOG(LogTemp, Display, TEXT("%p"), Item);
	if (Items.Contains(Item))
		Items[Item] += Count;
	else
		Items.Add(Item, Count);
}

bool UInventoryComponent::RemoveItem(UItem* Item, const int Count = 1)
{
	if (Items.Contains(Item) && Items[Item] >= Count)
	{
		Items[Item] -= Count;
		if (Items[Item] == 0)
			Items.Remove(Item);
		return true;
	}
	return false;
}

void UInventoryComponent::Loot(UInventoryComponent* Looter)
{
	for (const auto Item : Items)
		Looter->AddItem(Item.Key, Item.Value);
	Items.Empty();
	Looter->AddCoins(GetCoins());
	RemoveCoins(GetCoins());
	if (const auto OwnerActor = GetOwner())
		OwnerActor->Tags.Remove("Inventory");
}
