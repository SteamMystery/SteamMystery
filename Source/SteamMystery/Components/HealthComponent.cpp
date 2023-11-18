// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"
#include "SteamMystery/Game/MainGameMode.h"

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
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

	CurrentValue -= Damage;
	if (IsDead() && GameMode)
		GameMode->ActorDied(GetOwner());
}

bool UHealthComponent::IsDead() const
{
	return CurrentValue <= 0;
}