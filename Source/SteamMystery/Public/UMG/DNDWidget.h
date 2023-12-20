// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DNDWidget.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UDNDWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	class UImage* Image;

public:
	void SetImage(UMaterialInstance* InTexture) const;
	
};
