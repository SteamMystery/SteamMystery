// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Game/GameSave.h"

#include "Game/MainPlayerState.h"

UGameSave::UGameSave()
{
	Time = FDateTime::Now();
	ActionBar.SetNum(AMainPlayerState::ActionBarSize);
}
