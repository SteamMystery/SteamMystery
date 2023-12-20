// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Game/MainGameMode.h"

#include "Blueprint/UserWidget.h"
#include "SteamMystery/Public/Game/MainPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SteamMystery/Public/Characters/PlayerCharacter.h"

// ReSharper disable once CppMemberFunctionMayBeConst
void AMainGameMode::ActorDied(AActor* Actor)
{
	if (AGameCharacter* Character = Cast<AGameCharacter>(Actor))
	{
		if (Player == Actor)
			if (GameOverWidgetClass && MainPlayerController)
				if (const auto Widget = CreateWidget(MainPlayerController, GameOverWidgetClass))
				{
					MainPlayerController->SetShowMouseCursor(true);
					Widget->AddToViewport(999);
				}
		Character->HandleDeath();
	}
	OnActorDied.Broadcast(Actor);
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AGameCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
