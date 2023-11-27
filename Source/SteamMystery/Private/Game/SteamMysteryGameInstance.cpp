// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Game/SteamMysteryGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SteamMystery/Public/Game/ExtendedGameUserSettings.h"
#include "SteamMystery/Public/Game/GameSave.h"

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
