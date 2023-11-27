// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/UMG/Controls/Chooser.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"


bool UChooser::Initialize()
{
	const bool b = Super::Initialize();
	if (LeftButton)
		LeftButton->OnClicked.AddDynamic(this, &UChooser::Decrement);
	if (RightButton)
		RightButton->OnClicked.AddDynamic(this, &UChooser::Increment);
	OnChanged.Broadcast();
	return b;
}

void UChooser::Decrement()
{
	SetIndex(--ChosenIndex);
	OnChanged.Broadcast();
}

void UChooser::Increment()
{
	SetIndex(++ChosenIndex);
	OnChanged.Broadcast();
}

bool UChooser::CheckBorders() const
{
	LeftButton->SetIsEnabled(ChosenIndex != 0);
	RightButton->SetIsEnabled(ChosenIndex != Values.Num() - 1);
	return ChosenIndex >= 0 && ChosenIndex < Values.Num();
}

void UChooser::SetIndex(const int32 Index)
{
	ChosenIndex = Index;
	if (CheckBorders())
	{
		ChosenValue = Values[Index];
		Text->SetText(ChosenValue);
	}
}

FText UChooser::GetChosenValue() const
{
	return ChosenValue;
}
