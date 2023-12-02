// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TalkComponent.h"


inline AActor* UTalkComponent::GetCurrentNPC() const
{
	return CurrentNPC;
}

inline void UTalkComponent::SetCurrentNPC(AActor* Value)
{
	CurrentNPC = Value;
}
