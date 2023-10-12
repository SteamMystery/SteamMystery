// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

ARangedWeapon::ARangedWeapon()
{
	// FirePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Fire Point"));
	// FirePoint->SetupAttachment(RootComponent);
}

void ARangedWeapon::Fire()
{
	if (const APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		if (const AController* OwnerController = OwnerPawn->GetController())
		{
			// FVector Location;
			// FRotator Rotation;
			// OwnerController->GetPlayerViewPoint(Location, Rotation);

			const auto Location = GetMesh()->GetSocketLocation(TEXT("Ammo"));
			const auto Rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation();
			const auto Start = Location + Rotation.RotateVector(ProjectileOffset);
			//const FVector End = Location + Rotation.Vector() * MaxRange;

			//FVector Start = FirePoint->GetComponentLocation();

			const auto Transform = FTransform(Rotation, Start, FVector(0.1));
			if(ProjectileClass)
			{
				const auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Transform);
				Projectile->SetOwner(GetOwner());
			}
			// if (
			// 	FHitResult HitResult;
			// 	GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECC_GameTraceChannel1)
			// )
			// {
			// 	DrawDebugLine(GetWorld(), Start, HitResult.ImpactPoint, FColor::Blue, false, 5);
			// }
		}
	}
}
