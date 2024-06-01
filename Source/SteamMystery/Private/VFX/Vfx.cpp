// Fill out your copyright notice in the Description page of Project Settings.


#include "VFX/Vfx.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void FVfx::SpawnAtHitLocation(const UWorld* InWorld, const FHitResult& HitResult) const
{
	SpawnAtHitLocation(InWorld, HitResult, Scale);
}

void FVfx::SpawnAtHitLocation(const UWorld* InWorld, const FHitResult& HitResult, const FVector& InScale) const
{
	const auto RotFromZ = UKismetMathLibrary::MakeRotFromZ(HitResult.Normal);
	if (NiagaraSystem)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(InWorld,
													   NiagaraSystem,
													   HitResult.ImpactPoint,
													   RotFromZ,
													   InScale);
	else if (ParticleSystem)
		UGameplayStatics::SpawnEmitterAtLocation(InWorld,
												 ParticleSystem,
												 HitResult.ImpactPoint,
												 RotFromZ,
												 InScale);
}
