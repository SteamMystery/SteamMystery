// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

class UMeleeTraceComponent;
class UDataAssetCollections;
class UInputMappingContext;
class ADevice;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHandleDeathDelegate);

UCLASS()
class STEAMMYSTERY_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	// Sets default values for this character's properties
	AGameCharacter();

	UFUNCTION()
	void HandleDeath();

	UFUNCTION(BlueprintCallable)
	virtual bool Attack();

	UFUNCTION(BlueprintCallable)
	void Look(const FVector2D Value);
	
	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D Value);

	UPROPERTY(BlueprintReadWrite)
	bool bFire;
	
	UPROPERTY()
	UDataAssetCollections* Collections;

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* DefaultInputMapping;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* ActionBarInputMapping;

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FHandleDeathDelegate HandleDeathDelegate;

	UPROPERTY(SaveGame)
	ADevice* MainHand;

	UPROPERTY(EditDefaultsOnly, SaveGame)
	FName MainHandType;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UHealthComponent* Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USteamComponent* Steam;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UElectricityComponent* Electricity;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UInventoryComponent* Inventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMeleeTraceComponent* MeleeTraceComponent;
	
	UFUNCTION(BlueprintPure)
	ADevice* GetMainHand() const;

	UFUNCTION()
	void HandleMeleeAttack(UMeleeTraceComponent* ThisComponent, AActor* HitActor, const FVector& HitLocation, const FVector& HitNormal, FName HitBoneName);
	UFUNCTION(BlueprintCallable)
	void AttachDevice(const FName Device);
};

