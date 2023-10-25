// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectricityComponent.h"
#include "TimerManager.h"

UElectricityComponent::UElectricityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool UElectricityComponent::Consume(const float Value)
{
	const auto b = Super::Consume(Value);

	GetWorld()->GetTimerManager().SetTimer(RechargeTimer, this, &UElectricityComponent::Restore, RechargeTime);
	
	return b;
}

void UElectricityComponent::Restore()
{
	//UE_LOG(LogTemp, Display, TEXT("Recharge %f"), RechargeRate);
	Super::Restore(RechargeRate);
}
