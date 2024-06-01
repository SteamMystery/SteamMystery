// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Weapons/Projectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AISense_Damage.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	Mesh->SetupAttachment(Root);
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
	OnActorHit.AddUniqueDynamic(this, &AProjectile::OnHit);
	//Mesh->OnComponentHit.AddUniqueDynamic(this, &AProjectile::OnHit);

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, [this]
	{
		Destroy();
	}, ProjectileLifetime, false);

	FVector TossVelocity;
	if (!UGameplayStatics::SuggestProjectileVelocity(GetWorld(), TossVelocity, StartLocation, EndLocation,
	                                                 TossSpeed, false, 0, 0,
	                                                 ESuggestProjVelocityTraceOption::DoNotTrace,
	                                                 FCollisionResponseParams::DefaultResponseParam,
	                                                 TArray<AActor*>(), bDrawDebug))
		TossVelocity = UKismetMathLibrary::GetDirectionUnitVector(StartLocation, EndLocation) * TossSpeed;

	MovementComponent->SetVelocityInLocalSpace(TossVelocity);
}

void AProjectile::OnHit_Implementation(AActor* SelfActor,
                                       AActor* OtherActor,
                                       FVector NormalImpulse,
                                       const FHitResult& Hit)
{
	ImpactVfx.SpawnAtHitLocation(GetWorld(), Hit);
	DecalProps.SpawnAtHitLocation(GetWorld(), Hit);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetActorNameOrLabel())
	AActor* OwnerActor = GetOwner();

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(OwnerActor);

	if (ExplosionRadius > 0)
	{
		UGameplayStatics::ApplyRadialDamage(GetWorld(),
		                                    Damage,
		                                    Hit.ImpactPoint,
		                                    ExplosionRadius,
		                                    UDamageType::StaticClass(),
		                                    IgnoreActors,
		                                    this,
		                                    GetInstigatorController());
		ExplosionVfx.SpawnAtHitLocation(GetWorld(), Hit, FVector(ExplosionRadius / ExplosionRadiusScale));
	}
	else
	{
		UAISense_Damage::ReportDamageEvent(GetWorld(),
		                                   OtherActor,
		                                   OwnerActor,
		                                   Damage,
		                                   OwnerActor->GetActorLocation(),
		                                   Hit.ImpactPoint);

		UGameplayStatics::ApplyPointDamage(OtherActor,
		                                   Damage,
		                                   StartLocation,
		                                   Hit,
		                                   OwnerActor->GetInstigatorController(),
		                                   this,
		                                   UDamageType::StaticClass());
	}
	Destroy();
}
