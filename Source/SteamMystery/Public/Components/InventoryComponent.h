// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEAMMYSTERY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<UItem*, int32> Items;

	UPROPERTY(EditAnywhere)
	int Coins = 0;

public:
	UFUNCTION(BlueprintPure)
	int GetCoins() const;

	UFUNCTION(BlueprintCallable)
	void AddCoins(const int Value);

	UFUNCTION(BlueprintCallable)
	bool RemoveCoins(const int Value);

	UFUNCTION(BlueprintPure)
	TMap<UItem*, int32> GetItems() const;

	UFUNCTION(BlueprintCallable)
	void AddItem(UItem* Item, int Count);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UItem* Item, int Count);

	UFUNCTION(BlueprintCallable)
	void Loot(UInventoryComponent* Looter);
};
