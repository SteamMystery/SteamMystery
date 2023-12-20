// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/MonologueQuestTaskBlocking.h"

#include "GameFramework/PlayerState.h"
#include "HUDs/PlayerHUD.h"

UMonologueQuestTaskBlocking::UMonologueQuestTaskBlocking()
{
	UseActivateConditionOnly = false;
}

void UMonologueQuestTaskBlocking::OnQuestTaskActivated_Implementation()
{
	Super::OnQuestTaskActivated_Implementation();
	SetMonologue();
}

void UMonologueQuestTaskBlocking::OnQuestTaskLoaded_Implementation()
{
	Super::OnQuestTaskLoaded_Implementation();
	SetMonologue();
}

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

bool UMonologueQuestTaskBlocking::TaskShouldAnnounce_Implementation() const
{
	return false;
}

bool UMonologueQuestTaskBlocking::TaskShouldShowInUI_Implementation() const
{
	return false;
}

FString UMonologueQuestTaskBlocking::GetTaskName_Implementation() const
{
	return "Monologue Blocking";
}
