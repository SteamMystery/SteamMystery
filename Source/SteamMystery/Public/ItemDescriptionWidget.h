// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/ItemWidgets/ItemWidget.h"
#include "ItemDescriptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UItemDescriptionWidget : public UItemWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(meta=(BindWidget))
	class UContentWidget* DescriptionContainer;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Description;

	virtual void SyncItem(const FItem* Row) const override;
};
