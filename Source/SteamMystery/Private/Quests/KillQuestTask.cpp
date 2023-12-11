// Fill out your copyright notice in the Description page of Project Settings.


#include "Quests/KillQuestTask.h"

#include "Game/MainGameMode.h"
#include "Kismet/GameplayStatics.h"

UKillQuestTask::UKillQuestTask()
{
	UseActivateConditionOnly = false;
}

FString UKillQuestTask::GetTaskShortDescription_Implementation(const FQuestTaskPayload& PayloadIn,
                                                               const TArray<FString>& CustomPayloadDataIn) const
{
	FString LocalString = "Kill ";
	LocalString.Append(PayloadIn.StringA);
	return LocalString;
}

FString UKillQuestTask::GetTaskName_Implementation() const
{
	return "Kill";
}

void UKillQuestTask::OnQuestTaskActivated_Implementation()
{
	Super::OnQuestTaskActivated_Implementation();
	Bind();
}

void UKillQuestTask::OnQuestTaskLoaded_Implementation()
{
	Super::OnQuestTaskLoaded_Implementation();
	Bind();
}

void UKillQuestTask::CheckActor(const AActor* DiedActor)
{
	if(DiedActor->ActorHasTag(FName(InitialPayload.StringA)))
		EndQuestTask();
}

void UKillQuestTask::Bind()
{
	if (const auto GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		GameMode->OnActorDied.AddUniqueDynamic(this, &ThisClass::CheckActor);

}

bool UKillQuestTask::TaskShouldAnnounce_Implementation() const
{
	return true;
}

bool UKillQuestTask::TaskShouldShowInUI_Implementation() const
{
	return true;
}
