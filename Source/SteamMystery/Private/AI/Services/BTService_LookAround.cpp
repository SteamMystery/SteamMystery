// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/AI/Services/BTService_LookAround.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_LookAround::UBTService_LookAround()
{
	NodeName = TEXT("LookAround");
}

void UBTService_LookAround::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (const auto AaiController = OwnerComp.GetAIOwner())
		if (const auto MyPawn = AaiController->GetPawn())
		{
			FRotator CurrentPawnRotation;
			FVector CurrentPawnLocation;
			MyPawn->GetActorEyesViewPoint(CurrentPawnLocation, CurrentPawnRotation);
			const FRotator DesiredPawnRotation = CurrentPawnRotation + DesiredRotation;
			const FRotator SmoothTargetRotation = UKismetMathLibrary::RInterpTo_Constant(
				CurrentPawnRotation, DesiredPawnRotation, DeltaSeconds, SmoothFocusInterpSpeed);
			//DrawDebugLine(GetWorld(), CurrentPawnLocation, CurrentPawnLocation + SmoothTargetRotation.Vector() * 1000, FColor::Blue);
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), CurrentPawnLocation + SmoothTargetRotation.Vector() * 1000);
			// OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), CurrentPawnLocation + DesiredPawnRotation.Vector() * 1000);
		}
}

