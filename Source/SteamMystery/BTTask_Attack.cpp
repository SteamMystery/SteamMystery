// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "AIController.h"
#include "Characters/MainCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(const auto AIOwnerController = OwnerComp.GetAIOwner())
	{
		if(const auto Character = Cast<AMainCharacter>(AIOwnerController->GetPawn()))
		{
			Character->RangedAttack();
		}
	}
	
	return EBTNodeResult::Succeeded;
}
