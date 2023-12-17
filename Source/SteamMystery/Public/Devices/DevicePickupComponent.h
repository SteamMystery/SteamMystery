// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InteractionComponent.h"
#include "DevicePickupComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEAMMYSTERY_API UDevicePickupComponent : public UInteractionComponent
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void OnInteractCallback(const AMainPlayerController* InController);
	
	virtual void BeginPlay() override;
	
public:

	UPROPERTY(EditAnywhere)
	FName DeviceName;
};
