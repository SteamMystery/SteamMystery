// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* Actor) const;

	virtual void BeginPlay() override;
private:
	UPROPERTY()
	class APlayerCharacter* Player;

	UPROPERTY()
	class AMainPlayerController* MainPlayerController;
};
