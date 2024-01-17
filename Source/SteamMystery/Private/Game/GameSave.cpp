// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Game/GameSave.h"

#include "Game/MainPlayerState.h"

/**
 * 
 */
UGameSave::UGameSave()
{
	Time = FDateTime::Now();
	ActionBar.SetNum(AMainPlayerState::ActionBarSize);
}

bool UGameSave::SetRole(const ERole Value)
{
	if (Value == ERole::All || Value == ERole::None)
		return false;
	Role = Value;
	return true;
}

ERole UGameSave::GetRole() const
{
	return Role;
}
