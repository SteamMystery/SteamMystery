// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VFX/DecalProps.h"
#include "VFX/Vfx.h"
#include "Projectile.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;

UCLASS()
class STEAMMYSTERY_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

	UFUNCTION(BlueprintCallable)
	void SetDamageAndRadius(const float InDamage, const float InRadius = 0);

	UFUNCTION(BlueprintCallable)
	void SetPoints(const FVector Start, const FVector End);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileLifetime;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	FVector StartLocation;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	FVector EndLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn))
	float TossSpeed;

	UPROPERTY(EditDefaultsOnly)
	FVfx ImpactVfx;

	UPROPERTY(EditDefaultsOnly)
	FVfx ExplosionVfx;

	UPROPERTY(EditDefaultsOnly)
	FDecalProps DecalProps;

	UFUNCTION(BlueprintNativeEvent)
	void OnHit(UPrimitiveComponent* HitComp,
	           AActor* OtherActor,
	           UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse,
	           const FHitResult& HitResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn))
	float Damage = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn))
	float ExplosionRadius = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn))
	float ExplosionRadiusScale = 1;
};
