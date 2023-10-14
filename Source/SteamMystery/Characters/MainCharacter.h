// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UCameraComponent;
class AWeapon;

UCLASS()
class STEAMMYSTERY_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D Value);
	
	UFUNCTION()
	virtual void HandleDeath();

	UFUNCTION(BlueprintCallable)
	void Attack() const;

	UFUNCTION()
	virtual USkeletalMeshComponent* GetMainMesh() const;

protected:
	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* Health;

	UPROPERTY(BlueprintReadWrite)
	bool bHasRifle;
	
private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AWeapon* Weapon;

};
