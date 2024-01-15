// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InteractableComponent.h"
#include "DevicePickupComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEAMMYSTERY_API UDevicePickupComponent : public UInteractableComponent
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintNativeEvent)
	void OnInteractCallback(const AMainPlayerController* InController);
	
	virtual void BeginPlay() override;
	
public:

	UPROPERTY(EditAnywhere)
	FName DeviceName;
};
