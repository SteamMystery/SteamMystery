// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

UCLASS()
class STEAMMYSTERY_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();

	UFUNCTION()
	virtual void HandleDeath();


	UFUNCTION()
	virtual USkeletalMeshComponent* GetMainMesh() const;
	
	UFUNCTION(BlueprintCallable)
	virtual void Attack();
	
	UFUNCTION(BlueprintCallable)
	void Look(const FVector2D Value);

	UFUNCTION(BlueprintCallable)
	void Move(const FVector2D Value);


protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	class UHealthComponent* Health;
	
	UPROPERTY(EditAnywhere)
	class USteamComponent* Steam;
	
	UPROPERTY(EditAnywhere)
	class UElectricityComponent* Electricity;

	UPROPERTY(BlueprintReadWrite)
	bool bHasRifle;
	
	UPROPERTY()
	class ADevice* MainHand;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADevice> MainHandClass;
};
