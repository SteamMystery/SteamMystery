// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG/ItemWidget.h"
#include "DeviceWidget.generated.h"

class UInputMappingContext;
class ADevice;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UDeviceWidget : public UItemWidget
{
	GENERATED_BODY()
	virtual FReply NativeOnPreviewMouseButtonDown(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent
	) override;

	virtual void NativeOnDragDetected(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation
	) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ADevice> Actor;

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* ActionBarInputMapping;
	
	UFUNCTION(BlueprintPure)
	TSubclassOf<ADevice> GetActor() const;

	UFUNCTION(BlueprintCallable)
	void SetActor(TSubclassOf<ADevice> Value);
};
