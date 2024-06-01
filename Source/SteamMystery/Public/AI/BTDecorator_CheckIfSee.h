// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CheckIfSee.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UBTDecorator_CheckIfSee : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	virtual  bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
