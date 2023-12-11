// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppParameterMayBeConstPtrOrRef
#include "Components/NPCOverlapComponent.h"

#include "Characters/GameCharacter.h"
#include "Components/TalkComponent.h"


void UNPCOverlapComponent::OnBeginOverlap(UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent*,
                                          int32, bool, const FHitResult&)
{
	if (HealthComponent && !HealthComponent->IsDead())
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
	OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBeginOverlap);
	OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnEndOverlap);
	if (const auto OwningPlayer = Cast<AGameCharacter>(GetOwner()))
		HealthComponent = OwningPlayer->GetComponentByClass<UHealthComponent>();
}
