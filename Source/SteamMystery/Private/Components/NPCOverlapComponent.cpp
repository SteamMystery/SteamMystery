// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppParameterMayBeConstPtrOrRef
#include "Components/NPCOverlapComponent.h"
#include "TalkComponent.cpp"


void UNPCOverlapComponent::OnBeginOverlap(UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent*,
                                          int32, bool, const FHitResult&)
{
	if (const auto TalkComponent = OtherActor->GetComponentByClass<UTalkComponent>())
	{
		TalkComponent->Show(3);
		TalkComponent->SetCurrentNPC(GetOwner());
	}
}

void UNPCOverlapComponent::OnEndOverlap(UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent*, int32)
{
	if (const auto TalkComponent = OtherActor->GetComponentByClass<UTalkComponent>())
	{
		TalkComponent->Close(3);
		TalkComponent->SetCurrentNPC(nullptr);
	}
}

// Called when the game starts
void UNPCOverlapComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddUniqueDynamic(this, &UNPCOverlapComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddUniqueDynamic(this, &UNPCOverlapComponent::OnEndOverlap);
}
