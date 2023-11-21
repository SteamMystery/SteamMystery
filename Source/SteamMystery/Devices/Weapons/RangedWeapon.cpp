// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"
#include "SteamMystery/Characters/GameCharacter.h"

bool ARangedWeapon::Use()
{
	if (!Super::Use()) return false;
	const FVector Start = FirePoint->GetComponentLocation();
	const FRotator Rotation = FirePoint->GetComponentRotation();

	if (FireSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, Start, Rotation);
	if (FHitResult HitResult; Sweep(HitResult))
	{
		if (const auto OtherActor = HitResult.GetActor())
			if (const auto OwnerActor = GetOwner())
			{
				UE_LOG(LogTemp, Display, TEXT("%s"), *OtherActor->GetActorNameOrLabel());
				if (OtherActor && OtherActor != this && OtherActor != OwnerActor)
				{
					UAISense_Damage::ReportDamageEvent(GetWorld(), OtherActor, OwnerActor, Damage,
													   OwnerActor->GetActorLocation(), HitResult.ImpactPoint);
					UGameplayStatics::ApplyPointDamage(OtherActor,
					                                   Damage,
					                                   Start,
					                                   HitResult,
					                                   OwnerActor->GetInstigatorController(),
					                                   this,
					                                   UDamageType::StaticClass());
				}
				return true;
			}
	}
	return false;
}

bool ARangedWeapon::Sweep(FHitResult& HitResult) const
{
	if (const auto OwningCharacter = Cast<APawn>(GetOwner()))
		if (const auto OwnerController = OwningCharacter->GetController())
		{
			FRotator Rotator;
			FVector Start;
			OwnerController->GetPlayerViewPoint(Start, Rotator);
			const FVector End = Start + Rotator.Vector() * MaxFireDistance;
			auto Params = FCollisionQueryParams::DefaultQueryParam;
			Params.AddIgnoredActor(GetOwner());
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1, 0, 5);
			return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_EngineTraceChannel2, Params);
		}
	return false;
}

ARangedWeapon::ARangedWeapon()
{
	FirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(Mesh);
}
