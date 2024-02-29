// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Weapons/Projectile.h"

#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AISense_Damage.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	SetRootComponent(Mesh);
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
}

void AProjectile::SetDamageAndRadius(const float InDamage, const float InRadius)
{
	Damage = InDamage;
	ExplosionRadius = InRadius;
}

void AProjectile::SetPoints(const FVector Start, const FVector End)
{
	StartLocation = Start;
	EndLocation = End;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddUniqueDynamic(this, &AProjectile::OnHit);

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, [this]
	{
		Destroy();
	}, ProjectileLifetime, false);

	FVector TossVelocity;
	UGameplayStatics::SuggestProjectileVelocity(GetWorld(), TossVelocity, StartLocation, EndLocation,
	                                            TossSpeed, false, 0, 0,
	                                            ESuggestProjVelocityTraceOption::DoNotTrace,
	                                            FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(),
	                                            true);

	MovementComponent->SetVelocityInLocalSpace(TossVelocity);
}

void AProjectile::OnHit_Implementation(UPrimitiveComponent*,
                                       AActor* OtherActor,
                                       UPrimitiveComponent*,
                                       FVector,
                                       const FHitResult& HitResult)
{
	const auto RotFromZ = UKismetMathLibrary::MakeRotFromZ(HitResult.Normal);

	if (ImpactVfx.NiagaraSystem)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
		                                               ImpactVfx.NiagaraSystem,
		                                               HitResult.Location,
		                                               RotFromZ,
		                                               ImpactVfx.Scale);
	else if (ImpactVfx.ParticleSystem)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
		                                         ImpactVfx.ParticleSystem,
		                                         HitResult.Location,
		                                         RotFromZ,
		                                         ImpactVfx.Scale);

	if (DecalProps.Material)
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
		                                       DecalProps.Material,
		                                       DecalProps.Size,
		                                       HitResult.Location,
		                                       UKismetMathLibrary::MakeRotFromX(HitResult.Normal),
		                                       DecalProps.LifeSpan);
	AActor* OwnerActor = GetOwner();

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(OwnerActor);

	if (ExplosionRadius > 0)
	{
		UGameplayStatics::ApplyRadialDamage(
			GetWorld(),
			Damage,
			HitResult.ImpactPoint,
			ExplosionRadius,
			UDamageType::StaticClass(),
			IgnoreActors,
			this,
			GetInstigatorController());

		const FVector Scale(ExplosionRadius / ExplosionRadiusScale);

		if (ExplosionVfx.NiagaraSystem)
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
			                                               ExplosionVfx.NiagaraSystem,
			                                               HitResult.ImpactPoint,
			                                               RotFromZ,
			                                               Scale);

		else if (ExplosionVfx.ParticleSystem)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			                                         ExplosionVfx.ParticleSystem,
			                                         HitResult.ImpactPoint,
			                                         RotFromZ,
			                                         Scale);
	}
	else
	{
		UAISense_Damage::ReportDamageEvent(GetWorld(),
		                                   OtherActor,
		                                   OwnerActor,
		                                   Damage,
		                                   OwnerActor->GetActorLocation(), HitResult.ImpactPoint);

		UGameplayStatics::ApplyPointDamage(OtherActor,
		                                   Damage,
		                                   StartLocation,
		                                   HitResult,
		                                   OwnerActor->GetInstigatorController(),
		                                   this,
		                                   UDamageType::StaticClass());
	}
	Destroy();
}
