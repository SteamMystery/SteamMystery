// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/Item.h"
#include "Game/MainPlayerState.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLooted);

class UItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEAMMYSTERY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, int32> Items;

public:

	UPROPERTY(BlueprintAssignable)
	FOnLooted OnLooted;
	
	UFUNCTION(BlueprintCallable)
	void Loot(AMainPlayerState* Looter);
};
