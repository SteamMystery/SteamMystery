// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Game/MainGameMode.h"

#include "SteamMystery/Public/Game/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SteamMystery/Public/Characters/PlayerCharacter.h"

void AMainGameMode::ActorDied(AActor* Actor) const
{
	if (AGameCharacter* Character = Cast<AGameCharacter>(Actor))
		Character->HandleDeath();
	OnActorDied.Broadcast(Actor);
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
