// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Weapons/RangedWeapon.h"

#include "NiagaraFunctionLibrary.h"
#include "Devices/Weapons/Projectile.h"
#include "Game/MainPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "SteamMystery/Public/Characters/GameCharacter.h"

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

void ARangedWeapon::Recharge_Implementation()
{
	bIsRecharging = false;
	Ammo = PlayerState ? PlayerState->GetMaxCount(AmmoName, GetStats().FindRef(EStat::Ammo)) : -1;
}

bool ARangedWeapon::Use_Implementation()
{
	const float NeededAmmo = GetStats().FindRef(EStat::Ammo);
	if (bIsRecharging) return false;

	if (NeededAmmo > 0 && Ammo == 0)
	{
		StartRecharge();
		return false;
	}

	if (!Super::Use_Implementation()) return false;

	if (PlayerState && NeededAmmo > 0)
	{
		if (!PlayerState->RemoveItem(AmmoName, 1)) return false;
		Ammo--;
	}

	if (MuzzleVfx.NiagaraSystem)
		UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleVfx.NiagaraSystem,
		                                             FirePoint,
		                                             NAME_None,
		                                             FVector(ForceInit),
		                                             FRotator::ZeroRotator,
		                                             EAttachLocation::KeepRelativeOffset,
		                                             true);
	else if (MuzzleVfx.ParticleSystem)
		UGameplayStatics::SpawnEmitterAttached(MuzzleVfx.ParticleSystem, FirePoint);

	FHitResult HitResult;
	const auto TraceStart = FirePoint->GetComponentLocation();
	const auto TraceEnd = Sweep(HitResult, TraceStart, GetStats().FindRef(EStat::Range) * 100)
		                      ? HitResult.ImpactPoint
		                      : HitResult.TraceEnd;
	const FTransform Transform(FRotator::ZeroRotator, TraceStart);
	if (const auto Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass,
	                                                                        Transform,
	                                                                        GetOwner(),
	                                                                        GetInstigator()))
	{
		Projectile->SetDamageAndRadius(GetStats().FindRef(EStat::Damage), GetStats().FindRef(EStat::ExplosionRadius));
		Projectile->SetPoints(TraceStart, TraceEnd);
		Projectile->FinishSpawning(Transform);
	}

	if (const auto OwningCharacter = Cast<AGameCharacter>(GetOwner()))
		OwningCharacter->bFire = true;

	if (Ammo == 0)
		StartRecharge();

	return true;
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

void ARangedWeapon::BeginPlay()
{
	Super::BeginPlay();
	Recharge();
}
