// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/AI/Services/BTService_PlayerLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("UpdatePlayerLocation");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (const auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}
