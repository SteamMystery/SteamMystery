// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Weapons/MeleeWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"
#include "MeleeTraceComponent.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void AMeleeWeapon::Attack(AActor* HitActor, const FVector& HitLocation)
{
	const auto Damage = GetStats().FindRef(EStat::Damage);
	if (const auto OwnerActor = GetOwner())
		if (HitActor && HitActor != this && HitActor != OwnerActor)
		{
			UAISense_Damage::ReportDamageEvent(GetWorld(), HitActor, OwnerActor,
											   Damage,
											   OwnerActor->GetActorLocation(), HitLocation);
			UGameplayStatics::ApplyDamage(HitActor,
										  Damage,
										  OwnerActor->GetInstigatorController(),
										  OwnerActor,
										  UDamageType::StaticClass());
		}
}
