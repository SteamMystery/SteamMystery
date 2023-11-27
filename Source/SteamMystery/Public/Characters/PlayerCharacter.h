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
	APlayerCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FirstPersonCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* FirstPersonSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInteractionComponent* Grabber;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	virtual void BeginPlay() override;
public:
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	
};
