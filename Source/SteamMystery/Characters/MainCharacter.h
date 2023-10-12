// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "MainCharacter.generated.h"

UCLASS()
class STEAMMYSTERY_API AMainCharacter : public AGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* FirstPersonSkeletalMesh;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Look(const FVector2D Value);

	virtual USkeletalMeshComponent* GetMainMesh() const override;
};
