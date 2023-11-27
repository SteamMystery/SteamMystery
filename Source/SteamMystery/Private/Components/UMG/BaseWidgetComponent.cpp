// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Components/UMG/BaseWidgetComponent.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UBaseWidgetComponent::UBaseWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBaseWidgetComponent::Show(const int32 ZOrder) const
{
	if (Widget)
	{
		Widget->AddToViewport(ZOrder);
		if (ParentWidget)
			ParentWidget->RemoveFromParent();
	}
}

void UBaseWidgetComponent::Close(const int32 ZOrder) const
{
	if (Widget)
	{
		Widget->RemoveFromParent();
		if (ParentWidget)
			ParentWidget->AddToViewport(ZOrder);
	}
}

void UBaseWidgetComponent::SetParentWidget(UUserWidget* Value)
{
	ParentWidget = Value;
}

UUserWidget* UBaseWidgetComponent::GetWidget() const
{
	return Widget;
}


// Called when the game starts
void UBaseWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	static int Number = 0;
	const auto WidgetName = FString(TEXT("UBaseWidgetComponent ")) + FString::FormatAsNumber(Number++);
	Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Controller && WidgetClass)
		Widget = CreateWidget(Controller, WidgetClass, *WidgetName);
}
