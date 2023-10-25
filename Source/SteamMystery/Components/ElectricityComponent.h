// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatComponent.h"
#include "ElectricityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEAMMYSTERY_API UElectricityComponent : public UStatComponent
{
	GENERATED_BODY()

public:
	UElectricityComponent();
	virtual bool Consume(const float Value) override;
	void Restore();

private:
	UPROPERTY(EditAnywhere)
	float RechargeRate = 25.f;

	UPROPERTY(EditAnywhere)
	float RechargeTime = 5.f;

	UPROPERTY()
	FTimerHandle RechargeTimer;

};
