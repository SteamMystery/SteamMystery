// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Role.generated.h"

/**
 * 
*/

UENUM(BlueprintType)
enum class ERole
{
	None = 0,
	Knight = 1,
	Gunner = 2,
	Artificer = 4,
	All = -1
};

USTRUCT()
struct FRole : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERole Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* Icon;
};
