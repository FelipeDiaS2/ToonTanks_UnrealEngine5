// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public: 

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void handleDestruction();

private:

	void checkFireCondition();

	bool inFireRange();

	class ATank* tank;

	UPROPERTY(EditAnywhere)
	float fireRange;	

	FTimerHandle fireRateTimerHandle;
	
	float fireRate = 2;



};
