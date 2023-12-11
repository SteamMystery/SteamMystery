// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/ActionBarWidget.h"

#include "Components/PanelWidget.h"
#include "Game/BaseGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UMG/SkillSlotWidget.h"

void UActionBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (const auto Instance = Cast<UBaseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		DataTable = Instance->GetWeaponsDataTable();
}

void UActionBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (const APlayerController* Controller = GetOwningPlayer())
	{
		PlayerState = Controller->GetPlayerState<AMainPlayerState>();
		if (PlayerState)
		{
			PlayerState->ActionBarChanged.AddUniqueDynamic(this, &ThisClass::Sync);
			Skills->ClearChildren();
			for (int i = 0; i < PlayerState->ActionBarSize; i++)
				if (const auto Widget = CreateWidget<USkillSlotWidget>(GetOwningPlayer(), SkillSlotWidgetClass))
				{
					Widget->SetNumber(i);
					Widget->SetKey(PlayerState->GetKeyAt(i));
					Skills->AddChild(Widget);
				}
			PlayerState->ActionBarChanged.Broadcast();
		}
	}
}

void UActionBarWidget::Sync()
{
	if (PlayerState && DataTable)
		for (int i = 0; i < PlayerState->ActionBarSize; i++)
			if (const auto Child = Cast<USkillSlotWidget>(Skills->GetChildAt(i)))
				if (const auto Row = DataTable->FindRow<FItem>(PlayerState->GetDeviceAt(i), GetName(), false))
					Child->SetItem(*Row);
}
