// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Chooser.generated.h"

class UTextBlock;
class UButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChanged);

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UChooser : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;
public:
	UFUNCTION()
	void Decrement();
	UFUNCTION()
	void Increment();

	bool CheckBorders() const;
	UFUNCTION(BlueprintCallable)
	void SetIndex(int32 Index);
	UFUNCTION(BlueprintPure)
	FText GetChosenValue() const;

protected:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnChanged OnChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ChosenIndex = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText ChosenValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> Values;

	UPROPERTY(meta=(BindWidget))
	UButton* LeftButton;

	UPROPERTY(meta=(BindWidget))
	UButton* RightButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text;
};
