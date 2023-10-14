// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

void ARangedWeapon::Attack() const
{
	const auto Location = GetMesh()->GetSocketLocation(TEXT("Ammo"));
	const auto Rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
	const auto Start = Location + Rotation.RotateVector(ProjectileOffset);

	if (ProjectileClass)
	{
		const auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Start, Rotation);
		Projectile->SetOwner(GetOwner());
	}
}

// void ARangedWeapon::Fire() const
// {
// 	const auto Location = GetMesh()->GetSocketLocation(TEXT("Ammo"));
// 	const auto Rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
// 	const auto Start = Location + Rotation.RotateVector(ProjectileOffset);
//
// 	const auto Transform = FTransform(Rotation, Start, FVector(0.1));
// 	if (ProjectileClass)
// 	{
// 		const auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Transform);
// 		Projectile->SetOwner(GetOwner());
// 	}
// }
