// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Components/InventoryComponent.h"

#include "Components/PlayerInteractionComponent.h"
#include "Game/MainPlayerState.h"


void UInventoryComponent::Loot(AMainPlayerState* Looter)
{
	for (const auto Item : Items)
		Looter->AddItem(Item.Key, Item.Value);
	Items.Empty();
	if (const auto OwnerActor = GetOwner())
		OwnerActor->Tags.Remove(UPlayerInteractionComponent::LootTag);
}
