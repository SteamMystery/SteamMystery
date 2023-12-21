// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/MonologueQuestTaskBlocking.h"

#include "GameFramework/PlayerState.h"
#include "HUDs/PlayerHUD.h"


void UMonologueQuestTaskBlocking::SetMonologue()
{
	if (const auto PlayerState = Cast<APlayerState>(QuestManagerOwner))
		if (const auto Controller = Cast<APlayerController>(PlayerState->GetOwningController()))
			if (const auto HUD = Cast<APlayerHUD>(Controller->GetHUD()))
			{
				HUD->SetMonologue(InitialPayload.StringA);
				FTimerHandle UnusedHandle;
				GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [this, HUD]
				{
					HUD->SetMonologue("");
					EndQuestTask();
				}, InitialPayload.AmountInvolved, false);
			}
}


FString UMonologueQuestTaskBlocking::GetTaskName_Implementation() const
{
	return "Monologue Blocking";
}
