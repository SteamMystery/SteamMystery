// Fill out your copyright notice in the Description page of Project Settings.


#include "Options.h"

bool UOptions::Initialize()
{
	Super::Initialize();

	Sound->OnClicked.AddDynamic(this, &UOptions::OnSoundClicked);
	Graphics->OnClicked.AddDynamic(this, &UOptions::OnGraphicsClicked);
	Controls->OnClicked.AddDynamic(this, &UOptions::OnControlsClicked);
	
	return true;
}


void UOptions::OnSave()
{
}

void UOptions::OnCancel()
{
	RemoveFromParent();
}

void UOptions::OnSoundClicked()
{
	SetActiveWidget(0);
}

void UOptions::OnGraphicsClicked()
{
	SetActiveWidget(1);
}

void UOptions::OnControlsClicked()
{
	SetActiveWidget(2);
}

void UOptions::SetActiveWidget(const int32 Index)
{
	WidgetSwitcher->SetActiveWidgetIndex(Index);
	for (int32 i = 0; i < TabButtons.Num(); i++)
		TabButtons[i]->SetIsEnabled(Index != i);
}