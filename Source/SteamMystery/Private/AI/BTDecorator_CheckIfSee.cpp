// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_CheckIfSee.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_CheckIfSee::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (const auto AIOwnerController = OwnerComp.GetAIOwner())
		if (const auto Blackboard = OwnerComp.GetBlackboardComponent())
			if (const auto Other = Cast<AActor>(Blackboard->GetValueAsObject(GetSelectedBlackboardKey())))
				return AIOwnerController->LineOfSightTo(Other);
	return false;
}
