// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

class ADevice;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<ADevice> Item;

public:
	UFUNCTION(BlueprintPure)
	TSubclassOf<ADevice> GetItem() const;
	
	UFUNCTION(BlueprintCallable)
	void SetItem(TSubclassOf<ADevice> Value);
};
