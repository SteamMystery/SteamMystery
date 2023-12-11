// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Weapons/MeleeWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"
#include "MeleeTraceComponent.h"

void AMeleeWeapon::Attack(AActor* HitActor, const FVector& HitLocation)
{
	FEquipmentItem WeaponItem = GetStats();
	if (const auto OwnerActor = GetOwner())
		if (HitActor && HitActor != this && HitActor != OwnerActor)
		{
			UAISense_Damage::ReportDamageEvent(GetWorld(), HitActor, OwnerActor,
											   WeaponItem.Stats[EStat::Damage],
											   OwnerActor->GetActorLocation(), HitLocation);
			UGameplayStatics::ApplyDamage(HitActor,
										  WeaponItem.Stats[EStat::Damage],
										  OwnerActor->GetInstigatorController(),
										  OwnerActor,
										  UDamageType::StaticClass());
		}
}
