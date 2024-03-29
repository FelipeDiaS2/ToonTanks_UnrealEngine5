// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectileMesh;
	
	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	particleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	particleSystemComponent -> SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	projectileMesh -> OnComponentHit.AddDynamic(this, &AProjectile::onHit);

	if(launchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
	}
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProjectile::onHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto myOwner = GetOwner();

	if (myOwner == nullptr)
	{
		Destroy();

		return;
	} 
	
	auto myOwnerInstigator = myOwner -> GetInstigatorController();

	auto damageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != myOwner)
	{
		if(hitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());
		}

		UGameplayStatics::ApplyDamage(OtherActor, damage, myOwnerInstigator, this, damageTypeClass);

		if(hitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, hitParticle, GetActorLocation(), GetActorRotation());
		}

		if(hitCameraShakeClass)
		{
			GetWorld() -> GetFirstPlayerController() -> ClientStartCameraShake(hitCameraShakeClass);
		}
		
	}

	Destroy();

}
