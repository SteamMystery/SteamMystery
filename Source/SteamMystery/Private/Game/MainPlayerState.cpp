// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MainPlayerState.h"
#include "Quest/QuestManager.h"

AMainPlayerState::AMainPlayerState()
{
	QuestManager = CreateDefaultSubobject<UQuestManager>(TEXT("QuestManager"));
}
