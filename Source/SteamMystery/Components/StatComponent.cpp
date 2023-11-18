// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

UStatComponent::UStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

float UStatComponent::GetValue() const
{
	return CurrentValue;
}

float UStatComponent::GetPercentage() const
{
	return CurrentValue / MaxValue;
}

float UStatComponent::SetValue(const float Value)
{
	return this->CurrentValue = Value;
}

bool UStatComponent::Consume(const float Value)
{
	if (CanConsume(Value))
	{
		CurrentValue -= Value;
		return true;
	}
	return false;
}

bool UStatComponent::CanConsume(const float Value) const
{
	return CurrentValue >= Value;
}

void UStatComponent::Restore(const float Value)
{
	ToRestore = Value;
}

void UStatComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentValue = MaxValue;
}

void UStatComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ToRestore > 0)
	{
		CurrentValue += 0.5;
		ToRestore -= 0.5;
	}
}
