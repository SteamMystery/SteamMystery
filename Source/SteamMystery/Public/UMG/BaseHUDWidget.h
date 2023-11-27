// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UBaseHUDWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly)
	class APlayerHUD* HUD;
};
