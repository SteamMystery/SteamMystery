// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMMYSTERY_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void ShowWidget(const FText& InText) const;
	void HideWidget() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool Sweep(FHitResult& HitResult) const;
	UFUNCTION(BlueprintCallable)
	void Interact();
private:
	UPROPERTY()
	class AMainPlayerController* MainPlayerController = nullptr;
	
	UPROPERTY()
	class AMainPlayerState* PlayerState = nullptr;
	
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 100;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInteractionWidget> InteractionWidgetClass;

	UPROPERTY()
	UInteractionWidget* InteractionWidget = nullptr;
	FTimerHandle FocusTimerHandle;

protected:
	UPROPERTY(EditAnywhere)
	FText InteractText = FText::FromString("Interact");
	
	UPROPERTY(EditAnywhere)
	FText TalkText = FText::FromString("Talk");
	
	UPROPERTY(EditAnywhere)
	FText LootText = FText::FromString("Loot");

public:
	inline static const char* InteractTag = "Interact";
	inline static const char* LootTag = "Loot";
	inline static const char* NPCTag = "NPC";
};
