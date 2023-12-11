// Fill out your copyright notice in the Description page of Project Settings.

#include "SteamMystery/Public/Devices/Weapons/Weapon.h"

FWeaponItem AWeapon::GetWeaponStats() const
{
	if(const auto Row = RowHandle.GetRow<FWeaponItem>(GetName()))
		return *Row;
	return FWeaponItem();
}
