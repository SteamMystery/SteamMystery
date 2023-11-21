// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class STEAMMYSTERY_API APlayerCharacter : public AGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FirstPersonCamera;
	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// USkeletalMeshComponent* FirstPersonSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInteractionComponent* Grabber;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	virtual void BeginPlay() override;
public:
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// virtual USkeletalMeshComponent* GetMainMesh() const override;
	
};
