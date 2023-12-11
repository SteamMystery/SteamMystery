// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/BaseGameInstance.h"
#include "UMG/ItemWidgets/ItemWidget.h"
#include "ItemCollectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UItemCollectionWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void Sync();

	UPROPERTY()
	UBaseGameInstance* GameInstance;

	void FillItems(
		UPanelWidget* PanelWidget,
		const UDataTable* InDataTable,
		TMap<FName, int32> InItems,
		const TSubclassOf<UBaseItemWidget> ItemWidgetClass
	) const;
};
