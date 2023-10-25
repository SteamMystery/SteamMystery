// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

void AEnemyCharacter::DoAttack()
{
	switch (AttackCount)
	{
	case 0:
		AttackCount = 1;
		break;
	case 1:
		AttackCount = 0;
		break;
	default: ;
	}
	PlayAnimMontage(AnimMontage);
}

void AEnemyCharacter::Attack()
{

	if(IsAttacking)
		SaveAttack = true;
	else
	{
		IsAttacking = true;
		DoAttack();
	}
	
}

void AEnemyCharacter::ComboAttackSave()
{
	if(SaveAttack)
		SaveAttack = false;
	DoAttack();
}

void AEnemyCharacter::ResetCombo()
{
	AttackCount = 0;
	SaveAttack = false;
	IsAttacking = false;
}
