// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

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
	if (InteractionWidgetClass)
		if (APlayerController* OwningObject = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			InteractionWidget = CreateWidget(OwningObject, InteractionWidgetClass);
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (InteractionWidget)
	{
		if (FHitResult HitResult; Sweep(HitResult))
		{
			if (const auto HitActor = HitResult.GetActor())
				if (HitActor->ActorHasTag("Interactable"))
				{
					if (!InteractionWidget->IsInViewport())
						InteractionWidget->AddToViewport();
					return;
				}
		}
		if (InteractionWidget->IsInViewport())
			InteractionWidget->RemoveFromParent();
	}
}

bool UInteractionComponent::Sweep(FHitResult& HitResult) const
{
	const FVector Start = GetComponentLocation();
	const FVector End = Start + GetForwardVector() * MaxGrabDistance;
	const FCollisionShape Shape = FCollisionShape::MakeSphere(GrabRadius);
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_EngineTraceChannel2, Shape,
	                                        Params);
}

void UInteractionComponent::Interact() const
{
	if (FHitResult HitResult; Sweep(HitResult))
		if (const auto HitActor = HitResult.GetActor())
		{
			if (HitActor->ActorHasTag("Interactable"))
			{
				UE_LOG(LogTemp, Display, TEXT("HitActor :%s"), *HitActor->GetActorNameOrLabel())
				bool bContains = HitActor->ActorHasTag("Inventory");
				UE_LOG(LogTemp, Display, TEXT("HitActor :%d"), bContains)
				if (bContains)
				{
					const auto Inventory = HitActor->GetComponentByClass<UInventoryComponent>();
					UE_LOG(LogTemp, Display, TEXT("Inv: %p"), Inventory)
					if (Inventory)
						Inventory->Loot(Looter);
				}
			}
		}
}
