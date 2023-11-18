// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMysteryGameInstance.h"

#include "ExtendedGameUserSettings.h"
#include "GameSave.h"
#include "Kismet/GameplayStatics.h"

void USteamMysteryGameInstance::Init()
{
	Super::Init();
	SaveGame = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
	UExtendedGameUserSettings::GetExtendedGameUserSettings()->LoadSettings(true);
}

UGameSave* USteamMysteryGameInstance::GetSave() const
{
	return SaveGame;
}

void USteamMysteryGameInstance::SetSave(UGameSave* Value)
{
	SaveGame = Value;
}
