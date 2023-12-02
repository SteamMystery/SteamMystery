// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionBarChanged);

class ADevice;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAMMYSTERY_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

	UEquipmentComponent();

	virtual void BeginPlay() override;
protected:
	UPROPERTY(BlueprintReadOnly)
	class AGameCharacter* OwningCharacter = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ADevice>> Items;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ADevice>> ActionBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> ActionBarKeys;
	
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping = nullptr;

public:
	UFUNCTION(BlueprintPure)
	TArray<TSubclassOf<ADevice>> GetItems() const;

	UFUNCTION(BlueprintCallable)
	void SetInputMapping(UInputMappingContext* Value);

	UFUNCTION()
	void Action(const FInputActionValue& InputActionValue, int Index);

	static constexpr int ActionBarSize = 10;

	UFUNCTION(BlueprintPure)
	TSubclassOf<ADevice> GetDeviceAt(int32 Index);
	FText GetKeyAt(int32 Index);

	UPROPERTY(BlueprintAssignable)
	FOnActionBarChanged ActionBarChanged;

	UFUNCTION(BlueprintCallable)
	void SetAction(int32 Index, TSubclassOf<ADevice> Item);
		
};
