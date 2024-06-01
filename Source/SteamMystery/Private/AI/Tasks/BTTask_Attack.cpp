// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/AI/Tasks/BTTask_Attack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SteamMystery/Public/Characters/GameCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (const auto AIOwnerController = OwnerComp.GetAIOwner())
		if (const auto Character = Cast<AGameCharacter>(AIOwnerController->GetPawn()))
			if (Character->Attack(AttackName))
				Character->PlayAnimMontage(AnimMontage);
	return EBTNodeResult::Succeeded;
}
