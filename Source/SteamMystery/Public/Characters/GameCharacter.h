// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHandleDeathDelegate);

UCLASS()
class STEAMMYSTERY_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();

	UFUNCTION()
	void HandleDeath();

		UFUNCTION()
	virtual USkeletalMeshComponent* GetMainMesh() const;

	UFUNCTION(BlueprintCallable)
	virtual bool Attack();

	UFUNCTION(BlueprintCallable)
	void Look(const FVector2D Value);

	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D Value);

	UPROPERTY(BlueprintReadWrite)
	bool bFire;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UHealthComponent* Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USteamComponent* Steam;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UElectricityComponent* Electricity;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FHandleDeathDelegate HandleDeathDelegate;
	


	UPROPERTY(BlueprintReadWrite)
	bool bHasRifle;


	UPROPERTY()
	class ADevice* MainHand;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADevice> MainHandClass;

public:

	UPROPERTY(EditAnywhere)
	class UInventoryComponent* Inventory;

	UFUNCTION(BlueprintPure)
	ADevice* GetMainHand() const;
};
