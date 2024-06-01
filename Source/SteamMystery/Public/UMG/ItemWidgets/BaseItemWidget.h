// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Item.h"
#include "UMG/BaseHUDWidget.h"
#include "BaseItemWidget.generated.h"

class UButton;
class UItem;
class UImage;
class UTextBlock;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemClickedEvent, const FDataTableRowHandle&, Item, int32, Count);

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UBaseItemWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

public:
	// UFUNCTION(BlueprintCallable)
	// void SetItem(const FItem& Value, const int N);

	UFUNCTION(BlueprintCallable)
	void SetItem(const FDataTableRowHandle& Value, const int N);

	UPROPERTY(BlueprintAssignable)
	FOnItemClickedEvent OnClicked;

	UFUNCTION(BlueprintPure)
	FItem GetItem() const;
	virtual void SyncItem(const FItem* Row) const;

protected:
	virtual FReply NativeOnPreviewMouseButtonDown(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent
	) override;
	virtual void Sync() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemCount;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Name;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Count;

	UPROPERTY(meta=(BindWidget))
	UButton* Button;
};
