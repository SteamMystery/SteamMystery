// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Weapons/RangedWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"
#include "SteamMystery/Public/AI/MainAIController.h"
#include "SteamMystery/Public/Characters/GameCharacter.h"
#include "SteamMystery/Public/DataAssets/WeaponItem.h"

bool ARangedWeapon::Use()
{
	const UWeaponItem* WeaponItem = GetStats();
	if (!(WeaponItem && Super::Use())) return false;
	const FVector Start = FirePoint->GetComponentLocation();
	const FRotator Rotation = FirePoint->GetComponentRotation();

	if (FireSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, Start, Rotation);
	bool Result = false;
	if (FHitResult HitResult; Sweep(HitResult))
	{
		if(MuzzleParticles)
			UGameplayStatics::SpawnEmitterAttached(MuzzleParticles, FirePoint);
		if (const auto OtherActor = HitResult.GetActor())
			if (const auto OwnerActor = GetOwner())
			{
				if (OtherActor && OtherActor != this && OtherActor != OwnerActor)
				{
					UAISense_Damage::ReportDamageEvent(GetWorld(), OtherActor, OwnerActor, WeaponItem->Damage,
													   OwnerActor->GetActorLocation(), HitResult.ImpactPoint);
					UGameplayStatics::ApplyPointDamage(OtherActor,
													   WeaponItem->Damage,
													   Start,
													   HitResult,
													   OwnerActor->GetInstigatorController(),
													   this,
													   UDamageType::StaticClass());
				}
				Result = true;
			}
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
			FRotator Rotator;
			FVector Start;
			FVector Direction;
			double Length;
			OwnerController->GetPlayerViewPoint(Start, Rotator);
			if (const auto MainAIController = Cast<AMainAIController>(OwnerController))
				(MainAIController->GetFocalPoint() - Start).ToDirectionAndLength(Direction, Length);
			else
				Direction = Rotator.Vector();
			const FVector End = Start + Direction * GetStats()->Range;
			auto Params = FCollisionQueryParams::DefaultQueryParam;
			Params.AddIgnoredActor(GetOwner());
			return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_EngineTraceChannel2, Params);
		}
	return false;
}

ARangedWeapon::ARangedWeapon()
{
	FirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(Mesh);
}
