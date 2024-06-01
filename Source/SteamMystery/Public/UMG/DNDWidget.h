// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DNDWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UDNDWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UImage* Image;

public:
	void SetImage(UMaterial* InTexture) const;
	
};
