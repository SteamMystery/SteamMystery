// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Components/InteractionComponent.h"

#include "SteamMystery/Public/Components/InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Game/MainPlayerController.h"

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
	MainPlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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
				if (HitActor->ActorHasTag("Inventory"))
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
	FVector Start = GetComponentLocation();
	FRotator Rotator;
	MainPlayerController->GetPlayerViewPoint(Start, Rotator);
	const FVector End = Start + Rotator.Vector() /*GetForwardVector()*/ * MaxGrabDistance;
	const FCollisionShape Shape = FCollisionShape::MakeSphere(GrabRadius);
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(GetOwner());
	//DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 5, 0, 5);
	return GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_EngineTraceChannel2, Shape,
	                                        Params);
}

void UInteractionComponent::Interact()
{
	if (FHitResult HitResult; Sweep(HitResult))
		if (const auto HitActor = HitResult.GetActor())
			if (HitActor->ActorHasTag("Inventory"))
				if (const auto Inventory = HitActor->GetComponentByClass<UInventoryComponent>())
					Inventory->Loot(Looter);
}
