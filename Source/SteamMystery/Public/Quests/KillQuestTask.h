// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Task/BaseQuestTask.h"
#include "Task/QuestTaskInterface.h"
#include "KillQuestTask.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UKillQuestTask : public UBaseQuestTask, public IQuestTaskInterface
{
	GENERATED_BODY()

public:
	UKillQuestTask();
protected:
	virtual void OnQuestTaskActivated_Implementation() override;
	virtual void OnQuestTaskLoaded_Implementation() override;
	UFUNCTION()
	void CheckActor(const AActor* DiedActor);
	void Bind();

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
	virtual FString GetTaskShortDescription_Implementation(const FQuestTaskPayload& PayloadIn, const TArray <FString>& CustomPayloadDataIn) const override;

	/*Get task name for visual purposes*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Quest Task")
	FString GetTaskName() const;
	virtual FString GetTaskName_Implementation() const override;
};
