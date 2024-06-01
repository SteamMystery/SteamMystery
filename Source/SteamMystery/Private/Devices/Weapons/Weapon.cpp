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
			if (const auto AIController = Cast<AAIController>(OwnerController))
			{
				double Length;
				const auto Vector = AIController->GetFocalPoint() - Start;
				Vector.ToDirectionAndLength(Direction, Length);
			}
			else
				Direction = Rotation.Vector();
			const FVector TraceEnd = Start + Direction * Range;
			auto Params = FCollisionQueryParams::DefaultQueryParam;
			Params.AddIgnoredActor(GetOwner());
			Params.AddIgnoredActor(this);
			HitResult.TraceEnd = TraceEnd;
			return GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_EngineTraceChannel2, Params);
		}
	return false;
}
