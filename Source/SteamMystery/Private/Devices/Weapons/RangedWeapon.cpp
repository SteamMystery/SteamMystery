// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Weapons/RangedWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"
#include "SteamMystery/Public/AI/MainAIController.h"
#include "SteamMystery/Public/Characters/GameCharacter.h"
#include "SteamMystery/Public/DataAssets/WeaponItem.h"

bool ARangedWeapon::Use()
{
	const FEquipmentItem WeaponItem = GetStats();
	if (!Super::Use()) return false;
	const FVector Start = FirePoint->GetComponentLocation();
	const FRotator Rotation = FirePoint->GetComponentRotation();

	if (FireSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, Start, Rotation);
	bool Result = false;
	if (MuzzleParticles)
		UGameplayStatics::SpawnEmitterAttached(MuzzleParticles, FirePoint);
	if (FHitResult HitResult; Sweep(HitResult))
		if (const auto OtherActor = HitResult.GetActor())
			if (const auto OwnerActor = GetOwner())
			{
				if (OtherActor && OtherActor != this && OtherActor != OwnerActor)
				{
					UAISense_Damage::ReportDamageEvent(GetWorld(), OtherActor, OwnerActor,
					                                   WeaponItem.Stats[EStat::Damage],
					                                   OwnerActor->GetActorLocation(), HitResult.ImpactPoint);
					UGameplayStatics::ApplyPointDamage(OtherActor,
					                                   WeaponItem.Stats[EStat::Damage],
					                                   Start,
					                                   HitResult,
					                                   OwnerActor->GetInstigatorController(),
					                                   this,
					                                   UDamageType::StaticClass());
				}
				Result = true;
			}
	if (const auto OwningCharacter = Cast<AGameCharacter>(GetOwner()))
		OwningCharacter->bFire = Result;
	return Result;
}

bool ARangedWeapon::Sweep(FHitResult& HitResult) const
{
	if (const auto OwningCharacter = Cast<APawn>(GetOwner()))
		if (const auto OwnerController = OwningCharacter->GetController())
		{
			FVector Start;
			FRotator Rotation;
			FVector Direction;
			OwnerController->GetPlayerViewPoint(Start, Rotation);
			if (const auto MainAIController = Cast<AMainAIController>(OwnerController))
			{
				double Length;
				(MainAIController->GetFocalPoint() - Start).ToDirectionAndLength(Direction, Length);
			}
			else
				Direction = Rotation.Vector();
			const float Stat = GetWeaponStats().Stats[EStat::Range];
			const FVector End = Start + Direction * Stat;
			auto Params = FCollisionQueryParams::DefaultQueryParam;
			Params.AddIgnoredActor(GetOwner());
			Params.AddIgnoredActor(this);
			DrawDebugLine(GetWorld(), FirePoint->GetComponentLocation(), End, FColor::Red, false, 5, 0, 5);
			return GetWorld()->LineTraceSingleByChannel(HitResult, FirePoint->GetComponentLocation(), End,
			                                            ECC_EngineTraceChannel2, Params);
		}
	return false;
}

ARangedWeapon::ARangedWeapon()
{
	FirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(Root);
}
