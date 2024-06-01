// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/UMG/HUDWidget.h"

#include "Characters/GameCharacter.h"
#include "Components/PanelWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Devices/Weapons/RangedWeapon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "SteamMystery/Public/Components/Stats/ElectricityComponent.h"
#include "SteamMystery/Public/Components/Stats/HealthComponent.h"
#include "SteamMystery/Public/Components/Stats/SteamComponent.h"
#include "SteamMystery/Public/UMG/HealthBarBase.h"
#include "UMG/CircularProgressBar.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto OwningController = GetOwningPlayer())
	{
		PlayerCharacter = Cast<AGameCharacter>(OwningController->GetPawn());
		if (PlayerCharacter)
		{
			HealthComponent = PlayerCharacter->GetComponentByClass<UHealthComponent>();
			SteamComponent = PlayerCharacter->GetComponentByClass<USteamComponent>();
			ElectricityComponent = PlayerCharacter->GetComponentByClass<UElectricityComponent>();
		}
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

	if (RechargeProgressBar && AmmoContainer && PlayerCharacter)
		if (const auto MainHand = Cast<ARangedWeapon>(PlayerCharacter->GetMainHand()))
		{
			AmmoContainer->SetVisibility(ESlateVisibility::HitTestInvisible);
			const int32 Val = MainHand->GetCurrentAmmo();
			if (Ammo)
				Ammo->SetText(FText::AsNumber(Val));
			if (MaxAmmo)
				MaxAmmo->SetText(FText::AsNumber(MainHand->GetMaxAmmo() - Val));
			RechargeProgressBar->SetPercent(MainHand->GetRechargePercent());
		}
		else
		{
			AmmoContainer->SetVisibility(ESlateVisibility::Collapsed);
			RechargeProgressBar->SetPercent(0);
		}
}

void UHUDWidget::SetMonologue(const FText& InText) const
{
	Monologue->SetText(InText);
}
