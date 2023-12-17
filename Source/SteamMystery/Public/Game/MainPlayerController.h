// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/PlayerInteractionComponent.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMainPlayerController();
	
	void SetPlayerEnabledState(bool bPlayerEnabled);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPlayerInteractionComponent* InteractionComponent;
};
