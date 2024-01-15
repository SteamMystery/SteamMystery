// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CircularProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UCircularProgressBar : public UUserWidget
{
	GENERATED_BODY()

protected:
virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	
	UPROPERTY(EditDefaultsOnly)
	float Percent = 0.5;
	
	UPROPERTY(meta=(BindWidget))
	class UImage* Image;

	UPROPERTY(BlueprintReadOnly)
	UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* MaterialInstanceParent;
public:
	UFUNCTION(BlueprintCallable)
	void SetPercent(const float Value);
};
