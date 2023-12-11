// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/Item.h"
#include "Game/MainPlayerState.h"
#include "InventoryComponent.generated.h"

class UItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEAMMYSTERY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, int32> Items;

	UPROPERTY(EditAnywhere)
	int Coins = 0;

public:

	UFUNCTION(BlueprintCallable)
	void Loot(AMainPlayerState* Looter);
};
