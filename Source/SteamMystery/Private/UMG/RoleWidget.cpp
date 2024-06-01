// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/RoleWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Game/GameSave.h"
#include "Game/GameSaveSubsystem.h"
#include "Kismet/GameplayStatics.h"

void URoleWidget::NativePreConstruct()
{
	if(const auto Row = RowHandle.GetRow<FRole>(GetName()))
	{
		Icon->SetBrushFromMaterial(Row->Icon);
		Role = Row->Name;
		Name->SetText(UEnum::GetDisplayValueAsText(Role));
		Description->SetText(Row->Description);
	}
	Super::NativeConstruct();
}

void URoleWidget::StartGame_Implementation()
{
	if(const auto SaveSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UGameSaveSubsystem>())
	{
		if(const auto Save = SaveSubsystem->GetSave())
			Save->SetRole(Role);
		SaveSubsystem->ClearSaves();
		SaveSubsystem->StartNewGame();
	}
}

void URoleWidget::NativeConstruct()
{
	if(Button)
		Button->OnClicked.AddUniqueDynamic(this, &ThisClass::StartGame);
	Super::NativeConstruct();
}

