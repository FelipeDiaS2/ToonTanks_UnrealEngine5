// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void turnTurret(FVector targetPoint);

	void fire();

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* deathParticle;

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* capsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* baseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* turretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* projectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectile>	projectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* deathSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void handleDestruction();

};
