// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	void OnHoverChanged(const FText& Desc);

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
