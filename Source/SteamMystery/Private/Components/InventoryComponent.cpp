// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Components/InventoryComponent.h"

#include "Components/InteractionComponent.h"
#include "Game/MainPlayerState.h"


void UInventoryComponent::Loot(AMainPlayerState* Looter)
{
	for (const auto Item : Items)
		Looter->AddItem(Item.Key, Item.Value);
	Items.Empty();
	Looter->AddCoins(Coins);
	Coins = 0;
	if (const auto OwnerActor = GetOwner())
		OwnerActor->Tags.Remove(UInteractionComponent::InteractTag);
}
