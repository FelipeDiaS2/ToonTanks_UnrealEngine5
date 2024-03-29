// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* 	springArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* cameraComponent;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float turnRate;

	APlayerController* playerTankController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(float value);

	void Turn(float value);

	void handleDestruction();

	APlayerController* getPlayerTankController() const {return playerTankController;}

};
