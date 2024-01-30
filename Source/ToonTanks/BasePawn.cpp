// Fill out your copyright notice in the Description page of Project Settings.



#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "ParticleS/ParticleSystem.h"

#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = capsuleComponent;
		
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh -> SetupAttachment(RootComponent);
	
	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh -> SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	projectileSpawnPoint -> SetupAttachment(turretMesh);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::turnTurret(FVector targetPoint){

	FVector turretMeshLocation = turretMesh -> GetComponentLocation();

	FVector toTarget = targetPoint - turretMeshLocation;
	
	FRotator lookAtRotation = FRotator(0.f, toTarget.Rotation().Yaw, 0.f);

	turretMesh -> SetWorldRotation(FMath::RInterpTo(turretMesh -> GetComponentRotation(), lookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 10.f ));

}

void ABasePawn::fire()
{
	auto projectile = GetWorld() -> SpawnActor<AProjectile>(projectileClass, projectileSpawnPoint -> GetComponentLocation(), projectileSpawnPoint -> GetComponentRotation());

	projectile -> SetOwner(this);
}

void ABasePawn::handleDestruction()
{
	if (deathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, deathParticle, GetActorLocation(), GetActorRotation());
	}

	if(deathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, deathSound, GetActorLocation());
	}
	

}
