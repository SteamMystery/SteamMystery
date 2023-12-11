// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemCollectionWidget.h"
#include "ItemWidget.h"
#include "InventoryWidget.generated.h"


class UTextBlock;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UInventoryWidget : public UItemCollectionWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void Sync() override;
	
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* Items;
	
	UPROPERTY(meta=(BindWidget))
	class UItemDescriptionWidget* DescriptionContainer;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemWidget> ItemWidgetClass;
};
