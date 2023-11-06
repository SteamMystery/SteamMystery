// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

bool ARangedWeapon::Use() const
{
	if (!Super::Use()) return false;
	const FVector Start = FirePoint->GetComponentLocation();
	const FRotator Rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();

	if (ProjectileClass)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Start, Rotation);
		Projectile->SetOwner(GetOwner());
		if (FireSound)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, Start, Rotation);
		return true;
	}
	return false;
}

ARangedWeapon::ARangedWeapon()
{
	FirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(Mesh);
}
