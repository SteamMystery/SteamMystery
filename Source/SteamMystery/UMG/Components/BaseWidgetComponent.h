// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseWidgetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMMYSTERY_API UBaseWidgetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseWidgetComponent();

	UFUNCTION(BlueprintCallable)
	virtual void Show(const int32 ZOrder = 0) const;
	
	UFUNCTION(BlueprintCallable)
	virtual void Close() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* Widget = nullptr;
	
	UPROPERTY()
	APlayerController* Controller = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetClass;
};
