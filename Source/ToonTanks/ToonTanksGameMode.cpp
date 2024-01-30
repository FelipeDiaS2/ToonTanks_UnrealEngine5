// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

#include "ToonTanksGameMode.h"

void AToonTanksGameMode::actorDied(AActor* deadActor)
{

    if (tank == deadActor)
    {
        tank -> handleDestruction();

        if(tank -> getPlayerTankController())
        {
            toonTankPlayerController -> setPlayerEnableState(false); 
        }

        gameOver(false);
        
    }
    else if (ATower* tower = Cast<ATower>(deadActor))
    {

        tower -> handleDestruction();
        targetTowers--;

        if (targetTowers == 0)
        {   
            gameOver(true);
        }

    }

}


void AToonTanksGameMode::BeginPlay()
{

    Super::BeginPlay();


   handleStartDelay();

}

void AToonTanksGameMode::handleStartDelay()
{

    targetTowers = getTargetTowerCount();

    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    toonTankPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));


    if (toonTankPlayerController)
    {

        startGame();

        toonTankPlayerController -> setPlayerEnableState(false);

        FTimerHandle playerEnableTimerHandle;

        FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(toonTankPlayerController, &AToonTanksPlayerController::setPlayerEnableState,true);

        GetWorldTimerManager().SetTimer(playerEnableTimerHandle, timerDelegate, startDelay, false);

    }

}

int32 AToonTanksGameMode::getTargetTowerCount()
{

    TArray<AActor*> towersArray;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), towersArray);

    int32 towersCount = towersArray.Num();

    return towersCount;
}
