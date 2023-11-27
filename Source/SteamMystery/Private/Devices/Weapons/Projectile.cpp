// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamMystery/Public/Devices/Weapons/Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	SetRootComponent(Mesh);
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* /*HitComp*/,
                        AActor* OtherActor,
                        UPrimitiveComponent* /*OtherComp*/,
                        FVector /*NormalImpulse*/,
                        const FHitResult& /*HitResult*/)
{
	if (const auto OwnerActor = GetOwner())
	{
		UE_LOG(LogTemp, Display, TEXT("%s"), *OwnerActor->GetActorNameOrLabel());
		if (OtherActor && OtherActor != this && OtherActor != OwnerActor)
		{
			UGameplayStatics::ApplyDamage(OtherActor,
			                              Damage,
			                              OwnerActor->GetInstigatorController(),
			                              this,
			                              UDamageType::StaticClass());
			Destroy();
		}
	}
}
