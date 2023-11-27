// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetComponent.h"
#include "Components/ActorComponent.h"
#include "PauseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMMYSTERY_API UPauseComponent : public UBaseWidgetComponent
{
	GENERATED_BODY()

public:	
	virtual void Show(const int32 ZOrder) const override;
	
	virtual void Close(const int32 ZOrder) const override;
	
};
