// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemWidget.h"
#include "ItemWidget.generated.h"


class UDNDWidget;
class UItemIconWidget;

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UItemWidget : public UBaseItemWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativePreConstruct() override;

	virtual FReply NativeOnPreviewMouseButtonDown(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent
	) override;

	virtual void NativeOnDragDetected(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation
	) override;

	virtual void SyncItem(const FItem* const Row) const override;

	UPROPERTY(meta=(BindWidget))
	UImage* Image;

	UPROPERTY(EditAnywhere)
	FKey DragKey;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDNDWidget> UDNDWidgetClass;
};
