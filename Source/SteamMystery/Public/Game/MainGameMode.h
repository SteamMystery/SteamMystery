// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActorDiedEvent, const AActor*, DiedActor);
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void ActorDied(AActor* Actor);

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FActorDiedEvent OnActorDied;

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	
private:
	
	UPROPERTY()
	class AGameCharacter* Player;

	UPROPERTY()
	class AMainPlayerController* MainPlayerController;
};
