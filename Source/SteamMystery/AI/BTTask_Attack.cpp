// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "SteamMystery/Characters/GameCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(const auto AIOwnerController = OwnerComp.GetAIOwner())
	{
		if(const auto Character = Cast<AGameCharacter>(AIOwnerController->GetPawn()))
		{
			if(Character->Attack())
				Character->PlayAnimMontage(Character->GetAttackAnimMontage());
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Character failes"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Controller failes"))
	}
	
	return EBTNodeResult::Succeeded;
}
