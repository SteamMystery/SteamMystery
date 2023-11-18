// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UPauseComponent::Show(const int32 ZOrder) const
{
	Super::Show(ZOrder);
	if (Widget && Controller)
	{
		Controller->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(Controller, Widget);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void UPauseComponent::Close() const
{
	Super::Close();
	if (Controller)
	{
		Controller->SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(Controller);
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}
