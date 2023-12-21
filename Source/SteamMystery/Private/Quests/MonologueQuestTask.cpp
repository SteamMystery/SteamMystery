// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/MonologueQuestTask.h"

#include "GameFramework/PlayerState.h"
#include "HUDs/PlayerHUD.h"

UMonologueQuestTask::UMonologueQuestTask()
{
	UseActivateConditionOnly = false;
}

void UMonologueQuestTask::OnQuestTaskActivated_Implementation()
{
	Super::OnQuestTaskActivated_Implementation();
	SetMonologue();
}

void UMonologueQuestTask::OnQuestTaskLoaded_Implementation()
{
	Super::OnQuestTaskLoaded_Implementation();
	SetMonologue();
}

void UMonologueQuestTask::SetMonologue()
{
	if (const auto PlayerState = Cast<APlayerState>(QuestManagerOwner))
		if (const auto Controller = Cast<APlayerController>(PlayerState->GetOwningController()))
			if (const auto HUD = Cast<APlayerHUD>(Controller->GetHUD()))
			{
				HUD->SetMonologue(InitialPayload.StringA);
				FTimerHandle UnusedHandle;
				GetWorld()->GetTimerManager().SetTimer(UnusedHandle, [HUD]
				{
					HUD->SetMonologue("");
				}, InitialPayload.AmountInvolved, false);
			}
	EndQuestTask();
}


bool UMonologueQuestTask::TaskShouldAnnounce_Implementation() const
{
	return false;
}

bool UMonologueQuestTask::TaskShouldShowInUI_Implementation() const
{
	return false;
}

FString UMonologueQuestTask::GetTaskShortDescription_Implementation(const FQuestTaskPayload& PayloadIn, const TArray<FString>& CustomPayloadDataIn) const
{
	return FString();
}


FString UMonologueQuestTask::GetTaskName_Implementation() const
{
	return "Monologue";
}
