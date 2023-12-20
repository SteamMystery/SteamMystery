// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NPCAIController.h"

void ANPCAIController::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (const auto FocusActor = GetFocusActor();
		LineOfSightTo(FocusActor))
		if (const auto OwningCharacter = GetOwner())
		{
			const FVector V1 = GetFocalPoint();
			const FVector V2 = OwningCharacter->GetActorLocation();
			if (FVector::Dist(V1, V2) > 1000)
				return;
		}
	ClearFocus(EAIFocusPriority::Gameplay);
}
