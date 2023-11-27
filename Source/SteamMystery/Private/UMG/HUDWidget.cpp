// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/UMG/HUDWidget.h"

#include "Components/ProgressBar.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "SteamMystery/Public/Components/Stats/ElectricityComponent.h"
#include "SteamMystery/Public/Components/Stats/HealthComponent.h"
#include "SteamMystery/Public/Components/Stats/SteamComponent.h"
#include "SteamMystery/Public/UMG/HealthBarBase.h"


void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		HealthComponent = Player->GetComponentByClass<UHealthComponent>();
		SteamComponent = Player->GetComponentByClass<USteamComponent>();
		ElectricityComponent = Player->GetComponentByClass<UElectricityComponent>();
	}
}

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (HealthBar && HealthComponent)
		HealthBar->SetHealth(HealthComponent->GetPercentage());
	if (Steam && SteamComponent)
		Steam->SetPercent(SteamComponent->GetPercentage());
	if (Electricity && ElectricityComponent)
		Electricity->SetPercent(ElectricityComponent->GetPercentage());
}
