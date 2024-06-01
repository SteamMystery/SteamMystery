// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LookAround.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UBTService_LookAround : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_LookAround();
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SmoothFocusInterpSpeed = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator DesiredRotation;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
