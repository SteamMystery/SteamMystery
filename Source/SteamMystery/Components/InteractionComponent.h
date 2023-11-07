// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMMYSTERY_API UInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool Sweep(FHitResult& HitResult) const;
	UFUNCTION(BlueprintCallable)
	void Interact() const;

private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 100;

	UPROPERTY(EditAnywhere)
	class UInventoryComponent* Looter = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> InteractionWidgetClass;

	UPROPERTY()
	UUserWidget* InteractionWidget = nullptr;
};
