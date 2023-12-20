// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/DNDWidget.h"

#include "Components/Image.h"

void UDNDWidget::SetImage(UMaterialInstance* InTexture) const
{
	Image->SetBrushResourceObject(InTexture);
}
