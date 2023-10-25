// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

void ARangedWeapon::Use() const
{
	Super::Use();
	const auto Location = GetMesh()->GetSocketLocation(TEXT("Ammo"));
	const auto Rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
	const auto Start = Location + Rotation.RotateVector(ProjectileOffset);

	if (ProjectileClass)
	{
		const auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Start, Rotation);
		Projectile->SetOwner(GetOwner());
	}
}
