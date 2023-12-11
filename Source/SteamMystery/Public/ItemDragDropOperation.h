// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DataAssets/EquipmentItem.h"
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
	FName Item;

public:
	UFUNCTION(BlueprintPure)
	FName GetItem() const;
	
	UFUNCTION(BlueprintCallable)
	void SetItem(FName Value);
};
