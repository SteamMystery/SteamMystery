// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Task/BaseQuestTask.h"
#include "Task/QuestTaskInterface.h"
#include "MonologueQuestTask.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UMonologueQuestTask : public UBaseQuestTask, public IQuestTaskInterface
{
	GENERATED_BODY()
public:
	UMonologueQuestTask();
protected:
	virtual void OnQuestTaskActivated_Implementation() override;
	virtual void OnQuestTaskLoaded_Implementation() override;
	virtual void SetMonologue();
	//--------------------------------------------------------------------------------------------
	//------------------------------------------Quest Task Interface
	//--------------------------------------------------------------------------------------------
	/*Get announce UI configuration*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest Task")
	bool TaskShouldAnnounce() const;

	/*Get if the task should be shown in UI or not*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest Task")
	bool TaskShouldShowInUI() const;

	/*Get task short description*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest Task")
	FString GetTaskShortDescription(const FQuestTaskPayload& PayloadIn, const TArray <FString>& CustomPayloadDataIn) const;
	
	/*Get task name for visual purposes*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest Task")
	FString GetTaskName() const;
};
