// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

class AMainPlayerController;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, const AMainPlayerController*, InController);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMMYSTERY_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintAssignable)
	FOnInteract OnInteract;
		
};
