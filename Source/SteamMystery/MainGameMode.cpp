// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "MainPlayerController.h"
#include "Characters/GameCharacter.h"
#include "Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void AMainGameMode::ActorDied(AActor* Actor) const
{
	if (Actor == Player)
	{
		Player->HandleDeath();
		if (MainPlayerController)
			MainPlayerController -> SetPlayerEnabledState(false);
	}
	//Other deaths
	else if(AGameCharacter* Character = Cast<AGameCharacter>(Actor))
	{
		Character->HandleDeath();
	}
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
