// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UMG/BaseWidgetComponent.h"
#include "TalkComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEAMMYSTERY_API UTalkComponent : public UBaseWidgetComponent
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* CurrentNPC;

public:
	UFUNCTION(BlueprintPure)
	AActor* GetCurrentNPC() const;
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentNPC(AActor* Value);
};

