// Fill out your copyright notice in the Description page of Project Settings.


#include "VFX/DecalProps.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void FDecalProps::SpawnAtHitLocation(const UWorld* InWorld, const FHitResult& HitResult) const
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnedDecal to: %s"), *HitResult.GetActor()->GetActorNameOrLabel())
	if (Material)
		UGameplayStatics::SpawnDecalAtLocation(InWorld,
											   Material,
											   Size,
											   HitResult.ImpactPoint,
											   UKismetMathLibrary::MakeRotFromX(HitResult.ImpactNormal) + Rotation,
											   LifeSpan);
}
