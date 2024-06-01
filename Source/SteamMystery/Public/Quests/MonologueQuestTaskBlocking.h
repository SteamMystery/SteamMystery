// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonologueQuestTask.h"
#include "MonologueQuestTaskBlocking.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API UMonologueQuestTaskBlocking : public UMonologueQuestTask
{
	GENERATED_BODY()
	
protected:
	void ClearMonologue();
	virtual void SetMonologue() override;

	virtual FString GetTaskName_Implementation() const override;
};
