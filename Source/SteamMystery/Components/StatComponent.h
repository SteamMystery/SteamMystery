// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEAMMYSTERY_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatComponent();

	UFUNCTION(BlueprintPure)
	float GetValue() const;
	
	UFUNCTION(BlueprintPure)
	float GetPercentage() const;

	UFUNCTION(BlueprintCallable)
	float SetValue(const float Value);

	UFUNCTION(BlueprintCallable)
	virtual bool Consume(const float Value);
	
	UFUNCTION(BlueprintCallable)
	void Restore(const float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float MaxValue = 100.f;
	
	float CurrentValue = 0.f;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	float ToRestore = 0.f;
};
