// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidgetComponent.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBaseWidgetComponent::UBaseWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBaseWidgetComponent::Show(const int32 ZOrder) const
{
	if(Widget)
		Widget->AddToViewport(ZOrder);
}

void UBaseWidgetComponent::Close() const
{
	if(Widget)
		Widget->RemoveFromParent();
}


// Called when the game starts
void UBaseWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller)
		Widget = CreateWidget(Controller, WidgetClass);
	
}

