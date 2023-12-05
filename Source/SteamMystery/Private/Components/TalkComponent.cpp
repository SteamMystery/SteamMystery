// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TalkComponent.h"

AActor* UTalkComponent::GetCurrentNPC() const
{
	return CurrentNPC;
}

void UTalkComponent::SetCurrentNPC(AActor* Value)
{
	CurrentNPC = Value;
}
