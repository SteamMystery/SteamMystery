// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/MoveToWeaponRadius.h"

#include "AIController.h"
#include "Characters/GameCharacter.h"
#include "Devices/Device.h"

void UMoveToWeaponRadius::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	Super::OnInstanceCreated(OwnerComp);
	if (const auto AIOwnerController = OwnerComp.GetAIOwner())
		if(const auto Character = Cast<AGameCharacter>(AIOwnerController->GetPawn()))
			if(const auto MainHand = Character->GetMainHand())
				AcceptableRadius = MainHand->GetStats().Stats[EStat::Range];
}
