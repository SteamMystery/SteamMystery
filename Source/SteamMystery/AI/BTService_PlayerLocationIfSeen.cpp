// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("UpdatePlayerLocationIfSeen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (const auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		if (const auto AIOwnerController = OwnerComp.GetAIOwner())
		{
			if (AIOwnerController->LineOfSightTo(PlayerPawn))
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),
																	 PlayerPawn->GetActorLocation());
			else
				OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Controller failes"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Pawn failes"))
	}
}
