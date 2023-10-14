// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AMainAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AMainAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// if (LineOfSightTo(PlayerPawn))
	// {
	// 	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	// 	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), PlayerPawn->GetActorLocation());
	// 	// SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
	// 	// AcceptanceRadius = 200;
	// 	// MoveToActor(PlayerPawn, AcceptanceRadius);
	// }
	// else
	// {
	// 	GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	// 	// ClearFocus(EAIFocusPriority::Gameplay);
	// }
}
