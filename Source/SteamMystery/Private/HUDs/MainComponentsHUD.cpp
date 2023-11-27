// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/HUDs/MainComponentsHUD.h"

#include "SteamMystery/Public/Components/UMG/BaseWidgetComponent.h"
#include "SteamMystery/Public/Components/UMG/SavesComponent.h"


AMainComponentsHUD::AMainComponentsHUD()
{
	OptionsWidgetComponent = CreateDefaultSubobject<UBaseWidgetComponent>(TEXT("Options"));
	SavesWidgetComponent = CreateDefaultSubobject<USavesComponent>(TEXT("Saves"));
}
