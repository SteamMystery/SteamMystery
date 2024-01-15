// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/CircularProgressBar.h"

#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"

void UCircularProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
	if (MaterialInstanceParent)
	{
		MaterialInstance =
		UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), MaterialInstanceParent);
		Image->SetBrushFromMaterial(MaterialInstance);
	}
}

void UCircularProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetPercent(Percent);
}

void UCircularProgressBar::SetPercent(const float Value)
{
	if (MaterialInstance)
		MaterialInstance->SetScalarParameterValue(TEXT("Percent"), Value < 1 ? Value : 0);
}
