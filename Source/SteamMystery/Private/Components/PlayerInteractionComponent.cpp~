// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Components/PlayerInteractionComponent.h"

#include "AIController.h"
#include "SteamMystery/Public/Components/InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/InteractableComponent.h"
#include "Components/UMG/BaseWidgetComponent.h"
#include "Game/MainPlayerController.h"
#include "Game/MainPlayerState.h"
#include "GameFramework/HUD.h"
#include "HUDs/PlayerHUD.h"
#include "Npc/NPCManager.h"
#include "Quest/QuestManager.h"
#include "UMG/InteractionWidget.h"

// Sets default values for this component's properties
UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	MainPlayerController = Cast<AMainPlayerController>(GetOwner());
	if (InteractionWidgetClass && MainPlayerController)
		InteractionWidget = CreateWidget<UInteractionWidget>(MainPlayerController, InteractionWidgetClass);
	PlayerState = MainPlayerController->GetPlayerState<AMainPlayerState>();
}


void UPlayerInteractionComponent::ShowWidget(const FText& InText) const
{
	InteractionWidget->SetText(InText);
	if (!InteractionWidget->IsInViewport())
		InteractionWidget->AddToViewport();
}

void UPlayerInteractionComponent::HideWidget() const
{
	if (InteractionWidget->IsInViewport())
		InteractionWidget->RemoveFromParent();
}

// Called every frame
void UPlayerInteractionComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!InteractionWidget) return;
	if (FHitResult HitResult; Sweep(HitResult))
		if (const auto HitActor = HitResult.GetActor())
		{
			if (HitActor->ActorHasTag(LootTag))
				return ShowWidget(LootText);

			if (HitActor->GetComponentByClass<UNPCManager>())
				if (const auto HUD = Cast<APlayerHUD>(MainPlayerController->GetHUD()); HUD->TalkTabComponent)
					if (const UUserWidget* UserWidget = HUD->TalkTabComponent->GetWidget(); !UserWidget->IsInViewport())
						return ShowWidget(HitActor->ActorHasTag(InteractTag) ? InteractText : TalkText);

			if (HitActor->ActorHasTag(InteractTag))
				return ShowWidget(InteractText);
		}
	HideWidget();
}

bool UPlayerInteractionComponent::Sweep(FHitResult& HitResult) const
{
	if (!MainPlayerController) return false;
	FVector Start;
	FRotator Rotator;
	MainPlayerController->GetPlayerViewPoint(Start, Rotator);
	const FVector End = Start + Rotator.Vector() * MaxGrabDistance;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(MainPlayerController->GetPawn());
	//DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 5, 0, 5);
	return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_EngineTraceChannel2, Params);
}

void UPlayerInteractionComponent::Interact()
{
	FHitResult HitResult;
	if (!Sweep(HitResult)) return;
	if (const auto HitActor = HitResult.GetActor())
	{
		if (HitActor->ActorHasTag(NPCTag) && HitActor->GetComponentByClass<UNPCManager>())
			if (const auto HUD = Cast<APlayerHUD>(MainPlayerController->GetHUD()))
				if (const auto TalkTabComponent = HUD->TalkTabComponent)
				{
					PlayerState->QuestManager->ReachedNPC(HitActor);
					TalkTabComponent->Show(3);
					UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(MainPlayerController,
					                                               TalkTabComponent->GetWidget());
					MainPlayerController->SetShowMouseCursor(true);
					if (const auto Pawn = Cast<APawn>(HitActor))
						if (const auto Controller = Cast<AAIController>(Pawn->GetController()))
							Controller->SetFocus(MainPlayerController->GetPawn());
				}

		if (HitActor->ActorHasTag(LootTag))
			if (const auto InventoryComponent = HitActor->GetComponentByClass<UInventoryComponent>())
				InventoryComponent->Loot(PlayerState);

		if (HitActor->ActorHasTag(InteractTag))
			if (const auto InteractionComponent = HitActor->GetComponentByClass<UInteractableComponent>())
				InteractionComponent->OnInteract.Broadcast(MainPlayerController);
	}
}
