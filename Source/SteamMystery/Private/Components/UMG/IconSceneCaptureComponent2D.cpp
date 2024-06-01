// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UMG/IconSceneCaptureComponent2D.h"

UIconSceneCaptureComponent2D::UIconSceneCaptureComponent2D()
{
	bCaptureEveryFrame = false;
}

void UIconSceneCaptureComponent2D::BeginPlay()
{
	Super::BeginPlay();
	ShowOnlyActorComponents(GetOwner());
	CaptureScene();
}
