// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "InventoryComponent.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	Looter = GetOwner()->GetComponentByClass<UInventoryComponent>();
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInteractionComponent::Sweep(FHitResult& HitResult) const
{
	const FVector Start = GetComponentLocation();
	const FVector End = Start + GetForwardVector() * MaxGrabDistance;
	const FCollisionShape Shape = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_EngineTraceChannel2, Shape);
}

void UInteractionComponent::Interact() const
{
	if (FHitResult HitResult; Sweep(HitResult))
		if (const auto HitActor = HitResult.GetActor())
		{
			if (HitActor->Tags.Contains("Interactable"))
				return;
			if (HitActor->Tags.Contains("Inventory"))
				if (const auto Inventory = HitActor->GetComponentByClass<UInventoryComponent>())
					Inventory->Loot(Looter);
		}
}
