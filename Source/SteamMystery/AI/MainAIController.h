// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MainAIController.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API AMainAIController : public AAIController
{
	GENERATED_BODY()

	AMainAIController();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSensed(AActor* SourceActor, FAIStimulus Stimulus);

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	
	UPROPERTY()
	APawn* PlayerPawn;
	
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent;
};
