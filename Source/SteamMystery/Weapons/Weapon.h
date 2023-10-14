// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class STEAMMYSTERY_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();
	
	UFUNCTION(BlueprintCallable)
	virtual void Attack() const
	PURE_VIRTUAL(&AWeapon::Attack)

protected:
	
	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetMesh() const;

	
private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
};
