// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GameCharacter.h"
#include "DataAssets/Role.h"
#include "GameFramework/PlayerState.h"
#include "MainPlayerState.generated.h"

struct FInputActionValue;
class UGameSave;
class ADevice;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionBarChanged);
/**
 * 
 */

UCLASS()
class STEAMMYSTERY_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()

	UFUNCTION()
	void Sync(UGameSave* GameSave);
	virtual void BeginPlay() override;

	
public:
	static constexpr int ActionBarSize = 10;
	
	AMainPlayerState();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UQuestManager* QuestManager;

	UFUNCTION(BlueprintPure)
	ERole GetRole() const;
	
	UFUNCTION(BlueprintPure)
	TArray<FName> GetUpgrades(const FName DeviceName) const;
	
	UFUNCTION(BlueprintPure)
	TMap<FName, int32> GetItems() const;
	
	UFUNCTION(BlueprintCallable)
	void AddUpgrade(const FName DeviceName, const FName Value) const;

	UFUNCTION(BlueprintCallable)
	void AddItem(FName InItem, int InCount) const;

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(FName InItem, int InCount) const;
	
	UFUNCTION(BlueprintCallable)
	int32 GetMaxCount(FName InItem, int InCount) const;

	UFUNCTION(BlueprintPure)
	TMap<FName, int32> GetDevices() const;
	
	UFUNCTION(BlueprintCallable)
	void AddDevice(FName Item) const;
	
	UFUNCTION(BlueprintCallable)
	void RemoveDevice(FName Item) const;

	UFUNCTION(BlueprintPure)
	FName GetDeviceAt(int32 Index) const;
	
	UPROPERTY(BlueprintAssignable)
	FOnActionBarChanged ActionBarChanged;
	
	UFUNCTION(BlueprintCallable)
	void SetDevice(int32 Index, FName Item);
	
	FText GetKeyAt(int32 Index);

	UFUNCTION(BlueprintCallable)
	void SetInputMappingContext(class UInputMappingContext* InputMappingContext);
	
	UFUNCTION()
	void Action(const FInputActionValue& InputActionValue, int Index);
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputMappingContext* ActionBarInputMapping = nullptr;
	
	UPROPERTY(EditAnywhere)
	UGameSave* CurrentSave;
	

protected:
	UPROPERTY()
	AGameCharacter* OwningCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> ActionBarKeys;
};
