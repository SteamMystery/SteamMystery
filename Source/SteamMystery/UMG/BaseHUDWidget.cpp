// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUDWidget.h"

void UBaseHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerController* PController = GetOwningPlayer();
	auto hud = PController->GetHUD();
	
}
