// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Task/BaseQuestTask.h"
#include "Task/QuestTaskInterface.h"
#include "MonologueQuestTaskBlocking.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UMonologueQuestTaskBlocking : public UBaseQuestTask, public IQuestTaskInterface
{
	GENERATED_BODY()
public:
	UMonologueQuestTaskBlocking();
protected:
	virtual void OnQuestTaskActivated_Implementation() override;
	virtual void OnQuestTaskLoaded_Implementation() override;
	void SetMonologue();
	//--------------------------------------------------------------------------------------------
	//------------------------------------------Quest Task Interface
	//--------------------------------------------------------------------------------------------
	/*Get announce UI configuration*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest Task")
	bool TaskShouldAnnounce() const;
	virtual bool TaskShouldAnnounce_Implementation() const override;

	/*Get if the task should be shown in UI or not*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest Task")
	bool TaskShouldShowInUI() const;
	virtual bool TaskShouldShowInUI_Implementation() const override;

	/*Get task short description*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest Task")
	FString GetTaskShortDescription(const FQuestTaskPayload& PayloadIn, const TArray <FString>& CustomPayloadDataIn) const;
	
	/*Get task name for visual purposes*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest Task")
	FString GetTaskName() const;
	virtual FString GetTaskName_Implementation() const override;
};
