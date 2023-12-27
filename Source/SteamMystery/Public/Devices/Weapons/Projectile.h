// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class STEAMMYSTERY_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;

	UFUNCTION(BlueprintNativeEvent)
	void OnHit(UPrimitiveComponent* HitComp,
	           AActor* OtherActor,
	           UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse,
	           const FHitResult& HitResult);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;
	
	UPROPERTY(EditAnywhere)
	float ExplosionRadius = 1.f;
	
};
