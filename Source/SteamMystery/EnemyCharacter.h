// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GameCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class STEAMMYSTERY_API AEnemyCharacter : public AGameCharacter
{
	GENERATED_BODY()
	
public:
	void DoAttack();
	virtual void Attack() override;

	UFUNCTION(BlueprintCallable)
	void ComboAttackSave();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();
	
private:

	int AttackCount = 0;
	bool IsAttacking = false;
	bool SaveAttack = false;
	
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AnimMontage;
};
