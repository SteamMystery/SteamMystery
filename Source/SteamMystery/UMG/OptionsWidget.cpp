// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

bool UOptionsWidget::Initialize()
{
	Super::Initialize();
	TabButtons = TArray{SoundButton, GraphicsButton, ControlsButton};
	return true;
}

void UOptionsWidget::SetActiveWidget(const int32 Index)
{
	UE_LOG(LogTemp, Display, TEXT("%d"), Index)
	WidgetSwitcher->SetActiveWidgetIndex(Index);
	for (int32 i = 0; i < TabButtons.Num(); i++)
		TabButtons[i]->SetIsEnabled(Index != i);
}