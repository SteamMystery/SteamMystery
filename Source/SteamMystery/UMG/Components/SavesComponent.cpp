// Fill out your copyright notice in the Description page of Project Settings.


#include "SavesComponent.h"

#include "SteamMystery/UMG/SavesWidget.h"


void USavesComponent::ShowAsSaveable(const int32 ZOrder) const
{
	Cast<USavesWidget>(Widget)->SetSaveable(true);
	Super::Show(ZOrder);
}

void USavesComponent::Show(const int32 ZOrder) const
{
	Cast<USavesWidget>(Widget)->SetSaveable(false);
	Super::Show(ZOrder);
}
