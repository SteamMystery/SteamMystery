// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlotWidget.generated.h"

class ADevice;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API USkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativePreConstruct() override;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
protected:
		
	UPROPERTY(meta=(BindWidget))
	class UImage* Image;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* KeyTextBlock;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UEquipmentComponent* EquipmentComponent;

private:
	
	UPROPERTY(EditAnywhere)
	int32 Number;
	
	UPROPERTY(EditAnywhere)
	FText Key;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ADevice> Item;
	
public:
	UFUNCTION(BlueprintPure)
	int32 GetNumber() const;
	
	UFUNCTION(BlueprintPure)
	FText GetKey() const;
	
	UFUNCTION(BlueprintPure)
	TSubclassOf<ADevice> GetItem() const;

	UFUNCTION(BlueprintCallable)
	void SetNumber(int32 Value);
	
	UFUNCTION(BlueprintCallable)
	void SetKey(FText Value);
	
	UFUNCTION(BlueprintCallable)
	void SetItem(TSubclassOf<ADevice> Value);
	
	void SyncItem() const;
	void SyncKey() const;
};
