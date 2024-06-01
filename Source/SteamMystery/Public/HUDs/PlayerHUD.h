// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainComponentsHUD.h"
#include "Quest/QuestTypes.h"
#include "PlayerHUD.generated.h"

class UHUDWidget;
class UPauseComponent;

USTRUCT()
struct FMonologueQueueItem
{
	GENERATED_BODY()

	FString Text;

	int32 Amount;
};
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API APlayerHUD : public AMainComponentsHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	
	APlayerHUD();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UHUDWidget> HUDWidgetClass;
	
	UPROPERTY(EditAnywhere)
	UHUDWidget* HUDWidget;

public:
	UFUNCTION(BlueprintCallable)
	void SetMonologue(const FString& InString) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPauseComponent* PauseComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPauseComponent* InventoryComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPauseComponent* EquipmentComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBaseWidgetComponent* TalkTabComponent;
};
