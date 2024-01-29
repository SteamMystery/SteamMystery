// Fill out your copyright notice in the Description page of Project Settings.

#include "SteamMystery/Public/Devices/Weapons/Weapon.h"

#include "AI/MainAIController.h"

bool AWeapon::Sweep(FHitResult& HitResult, const FVector& TraceStart, const float Range) const
{
	if (const auto OwningCharacter = Cast<APawn>(GetOwner()))
		if (const auto OwnerController = OwningCharacter->GetController())
		{
			FVector Start;
			FRotator Rotation;
			FVector Direction;
			OwnerController->GetPlayerViewPoint(Start, Rotation);
			if (const auto MainAIController = Cast<AMainAIController>(OwnerController))
			{
				double Length;
				(MainAIController->GetFocalPoint() - Start).ToDirectionAndLength(Direction, Length);
			}
			else
				Direction = Rotation.Vector();
			const FVector End = Start + Direction * Range;
			auto Params = FCollisionQueryParams::DefaultQueryParam;
			Params.AddIgnoredActor(GetOwner());
			Params.AddIgnoredActor(this);
			//DrawDebugLine(GetWorld(), FirePoint->GetComponentLocation(), End, FColor::Red, false, 15);
			GetWorld()->LineTraceSingleByChannel(HitResult,
												 TraceStart,
												 End,
												 ECC_EngineTraceChannel2,
												 Params);
			return true;
		}
	return false;
}
