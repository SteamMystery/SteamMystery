// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "MoveToWeaponRadius.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UMoveToWeaponRadius : public UBTTask_MoveTo
{
	GENERATED_BODY()
	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
};
