// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/BTService_CheckIfDead.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/GameCharacter.h"
#include "Components/Stats/HealthComponent.h"

bool UBTService_CheckIfDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if(const auto Blackboard = OwnerComp.GetBlackboardComponent())
	if (const auto Character = Cast<AGameCharacter>(Blackboard->GetValueAsObject(GetSelectedBlackboardKey())))
		if (const auto Health = Character->Health)
			return Health->IsDead();
	return false;
}
