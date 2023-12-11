// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Components/InteractionComponent.h"

#include "SteamMystery/Public/Components/InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/UMG/BaseWidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Game/MainPlayerController.h"
#include "Game/MainPlayerState.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	//Looter = GetOwner()->GetComponentByClass<UInventoryComponent>();
	MainPlayerController = Cast<AMainPlayerController>(GetOwner());
	if (InteractionWidgetClass && MainPlayerController)
		InteractionWidget = CreateWidget(MainPlayerController, InteractionWidgetClass);
	PlayerState = PlayerState = MainPlayerController->GetPlayerState<AMainPlayerState>();
}


// Called every frame
void UInteractionComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (InteractionWidget)
	{
		if (FHitResult HitResult; Sweep(HitResult))
			if (const auto HitActor = HitResult.GetActor())
				if (HitActor->ActorHasTag(InteractTag))
				{
					if (!InteractionWidget->IsInViewport())
						InteractionWidget->AddToViewport();
					return;
				}
		if (InteractionWidget->IsInViewport())
			InteractionWidget->RemoveFromParent();
	}
}

bool UInteractionComponent::Sweep(FHitResult& HitResult)
{
	FVector Start;
	FRotator Rotator;
	MainPlayerController->GetPlayerViewPoint(Start, Rotator);
	const FVector End = Start + Rotator.Vector() /*GetForwardVector()*/ * MaxGrabDistance;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(MainPlayerController->GetPawn());
	//DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 5, 0, 5);
	return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_EngineTraceChannel2, Params);
}

void UInteractionComponent::Interact()
{
	if (FHitResult HitResult; Sweep(HitResult))
		if (const auto HitActor = HitResult.GetActor())
			if (HitActor->ActorHasTag(InteractTag))
			{
				if (const auto Inventory = HitActor->GetComponentByClass<UInventoryComponent>())
					Inventory->Loot(PlayerState);
				if (const auto WidgetComponent = HitActor->GetComponentByClass<UBaseWidgetComponent>())
					WidgetComponent->Show(3);
			}
}
