// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHUDWidget.h"
#include "InventoryWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UInventoryWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UInventoryComponent* Inventory;
	
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* Items;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Description;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Coins;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UItemWidget> ItemWidgetClass;
};
