// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/MoveToWeaponRadius.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/GameCharacter.h"
#include "Devices/Device.h"


EBTNodeResult::Type UMoveToWeaponRadius::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto AIOwnerController = OwnerComp.GetAIOwner())
		if (const auto Character = Cast<AGameCharacter>(AIOwnerController->GetPawn()))
			if (const auto MainHand = Character->GetMainHand())
			{
				const auto AcceptableRadius = MainHand->GetStats().FindRef(EStat::Range) * 100;
				const auto Blackboard = OwnerComp.GetBlackboardComponent();
				if (const auto Actor = Cast<AActor>(Blackboard->GetValueAsObject(GetSelectedBlackboardKey())))
					AIOwnerController->MoveToActor(Actor, AcceptableRadius);
			}
	return EBTNodeResult::Succeeded;
}
