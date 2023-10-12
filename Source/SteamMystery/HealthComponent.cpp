// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}



void UHealthComponent::DamageTaken(AActor* DamagedActor,
                                   const float Damage,
                                   const UDamageType* DamageType,
                                   AController* Instigator,
                                   AActor* DamageCauser)
{
	if (Damage <= 0) return;

	Health -= Damage;
	if (IsDead() && GameMode)
		GameMode->ActorDied(GetOwner());
}

bool UHealthComponent::IsDead() const
{
	return Health <= 0;
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

float UHealthComponent::GetHealthPercentage() const
{
	return Health / MaxHealth;
}

float UHealthComponent::SetHealth(const float Value)
{
	return Health = Value;
}

