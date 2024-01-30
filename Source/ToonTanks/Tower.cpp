// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"



void ATower::BeginPlay()
{
	Super::BeginPlay();

    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

	GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATower::checkFireCondition, fireRate, true );

}


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (tank)
	{
		if (inFireRange())
		{
		
			turnTurret(tank -> GetActorLocation());
		
		}

	}

}

void ATower::checkFireCondition()
{
		
	if (inFireRange())
	{
		fire();
	}

}


bool ATower::inFireRange()
{
	if (tank)
	{
		float distance = FVector::Dist(GetActorLocation(), tank -> GetActorLocation());
		
		if(distance <= fireRange)
		{
			return true;
		}
	}

	return false;

}


void ATower::handleDestruction()
{

	Super::handleDestruction();

	Destroy();


}

