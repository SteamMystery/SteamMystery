// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_GetRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetRandomLocation::UBTTask_GetRandomLocation()
{
	NodeName = "Go to random location in radius";
}

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (const auto AIOwnerController = OwnerComp.GetAIOwner())
		if (const auto Pawn = AIOwnerController->GetPawn())
			if (const UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
				if (FNavLocation ResultLocation;
					NavSys->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, ResultLocation))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ResultLocation.Location);
					return EBTNodeResult::Succeeded;
				}
	return EBTNodeResult::Failed;
}
