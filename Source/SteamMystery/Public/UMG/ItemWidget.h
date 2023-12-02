// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UItem;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

	void Sync();

public:
	UFUNCTION(BlueprintCallable)
	void SetItem(UItem* Value, const int N);
	
	UFUNCTION(BlueprintCallable)
	void SetDescBlock(UTextBlock* TextBlock);

	UFUNCTION()
	void OnHovered();
	
	UFUNCTION()
	void OnUnhovered();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItem* Item;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemCount;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Name;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Count;
	
	UPROPERTY(meta=(BindWidget))
	UImage* Image;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* Button;

	UPROPERTY()
	UTextBlock* DescriptionTextBlock;

	UPROPERTY(EditAnywhere)
	FKey DragKey;
};
