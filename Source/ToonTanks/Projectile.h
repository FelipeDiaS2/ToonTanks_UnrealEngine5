// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* projectileMesh;

	UPROPERTY(EditAnywhere, Category = "Projectile Movement Component")
	class UProjectileMovementComponent* projectileMovementComponent;

	// This is a callback function to a multicast delegate function that requires a list of specific input parameters
	// the OnComponentHit has a type of FHitComponentSignature, thats where we can find the input parameters to pass for our function
	UFUNCTION()
	void onHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* hitParticle;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* particleSystemComponent;

	UPROPERTY(EditAnywhere)
	class USoundBase* hitSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* launchSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> hitCameraShakeClass;

};
