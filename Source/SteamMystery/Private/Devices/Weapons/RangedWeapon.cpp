// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Weapons/RangedWeapon.h"

#include "Game/MainPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Perception/AISense_Damage.h"
#include "SteamMystery/Public/AI/MainAIController.h"
#include "SteamMystery/Public/Characters/GameCharacter.h"


void ARangedWeapon::Recharge()
{
	bIsRecharging = false;
	if (PlayerState)
		Ammo = PlayerState->GetMaxCount(AmmoName, GetStats().FindRef(EStat::Ammo));
	else
		Ammo = -1;
}

bool ARangedWeapon::StartRecharge_Implementation()
{
	if (const auto Recharge = GetStats().FindRef(EStat::Recharge); Recharge > 0)
	{
		if (PlayerState && (GetStats().FindRef(EStat::Ammo) > 0 && PlayerState->GetMaxCount(AmmoName, 1) == 0))
			return false;
		bIsRecharging = true;
		GetWorld()->GetTimerManager().SetTimer(RechargeTimer, this, &ThisClass::Recharge, Recharge);
	}
	return true;
}

bool ARangedWeapon::Use_Implementation()
{
	const float NeededAmmo = GetStats().FindRef(EStat::Ammo);
	if (bIsRecharging || !CheckRole())
		return false;

	if (NeededAmmo > 0 && Ammo == 0)
	{
		StartRecharge();
		return false;
	}

	if (!Super::Use_Implementation())
		return false;

	if (PlayerState && NeededAmmo > 0)
	{
		if (!PlayerState->RemoveItem(AmmoName, 1))
			return false;
		Ammo--;
	}

	if (MuzzleParticles)
		UGameplayStatics::SpawnEmitterAttached(MuzzleParticles, FirePoint);

	if (FHitResult HitResult; Sweep(HitResult))
		if (const auto OtherActor = HitResult.GetActor())
			if (const auto OwnerActor = GetOwner())
			{
				const auto Damage = GetStats().FindRef(EStat::Damage);
				if (const auto Radius = GetStats().Find(EStat::ExplosionRadius))
				{
					const TArray<AActor*> IgnoreActors;
					UGameplayStatics::ApplyRadialDamage(GetWorld(),
					                                    Damage,
					                                    HitResult.ImpactPoint,
					                                    *Radius,
					                                    UDamageType::StaticClass(),
					                                    IgnoreActors,
					                                    this,
					                                    OwnerActor->GetInstigatorController());
					if (ExplosionParticles)
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
						                                         ExplosionParticles,
						                                         HitResult.ImpactPoint,
						                                         FRotator::ZeroRotator,
						                                         FVector(*Radius / RadiusScale));
				}
				else
				{
					UAISense_Damage::ReportDamageEvent(GetWorld(), OtherActor, OwnerActor,
					                                   Damage,
					                                   OwnerActor->GetActorLocation(), HitResult.ImpactPoint);
					UGameplayStatics::ApplyPointDamage(OtherActor,
					                                   Damage,
					                                   FirePoint->GetComponentLocation(),
					                                   HitResult,
					                                   OwnerActor->GetInstigatorController(),
					                                   this,
					                                   UDamageType::StaticClass());
				}
			}

	if (const auto OwningCharacter = Cast<AGameCharacter>(GetOwner()))
		OwningCharacter->bFire = true;


	if (Ammo == 0)
		StartRecharge();

	return true;
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
			const FVector End = Start + Direction * GetStats().FindRef(EStat::Range) * 100;
			auto Params = FCollisionQueryParams::DefaultQueryParam;
			Params.AddIgnoredActor(GetOwner());
			Params.AddIgnoredActor(this);
			//DrawDebugLine(GetWorld(), FirePoint->GetComponentLocation(), End, FColor::Red, false, 15);
			GetWorld()->LineTraceSingleByChannel(HitResult,
			                                     FirePoint->GetComponentLocation(),
			                                     End,
			                                     ECC_EngineTraceChannel2,
			                                     Params);
			return true;
		}
	return false;
}

ARangedWeapon::ARangedWeapon()
{
	FirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(Root);
}

int32 ARangedWeapon::GetCurrentAmmo() const
{
	return Ammo;
}

float ARangedWeapon::GetRechargePercent() const
{
	const FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	const auto Remains = TimerManager.GetTimerRemaining(RechargeTimer);
	const auto All = TimerManager.GetTimerRate(RechargeTimer);
	return Remains / All;
}

float ARangedWeapon::GetMaxAmmo() const
{
	if (PlayerState)
		return PlayerState->GetItems().FindRef(AmmoName);
	return 0;
}
