// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
	void startGame();


	UFUNCTION(BlueprintImplementableEvent)
	void gameOver(bool bWonGame);


public:

	void actorDied(AActor* deadActor);


private:

	class ATank* tank;

	class AToonTanksPlayerController* toonTankPlayerController;

	float startDelay = 3.f;

	void handleStartDelay();

	int32 targetTowers = 0;

	int32 getTargetTowerCount();


	
};
