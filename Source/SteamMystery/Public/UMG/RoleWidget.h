// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataAssets/Role.h"
#include "Engine/DataTable.h"
#include "RoleWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API URoleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativePreConstruct() override;
	UFUNCTION(BlueprintNativeEvent)
	void StartGame();	
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle RowHandle;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button;
	
	UPROPERTY(meta=(BindWidget))
	UImage* Icon;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Name;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Description;
	
	ERole Role;
};
