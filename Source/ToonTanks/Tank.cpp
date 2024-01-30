// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArmComponent -> SetupAttachment(RootComponent); 

    cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    cameraComponent -> SetupAttachment(springArmComponent);

}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	playerTankController = Cast<APlayerController>(GetController());

}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult hitResult;
	playerTankController -> GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);

	if(playerTankController)
	{

		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 12.f, 12.f, FColor::Green, false, -1.f);	

		turnTurret(hitResult.ImpactPoint);

	}

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent -> BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent -> BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::fire);
}

void ATank::Move(float value)
{

	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	FVector deltaLocation(0.f);
	deltaLocation.X = value * deltaTime * speed;

	AddActorLocalOffset(deltaLocation,true);


}

void ATank::Turn(float value)
{

	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	
	FRotator deltaRotation = FRotator::ZeroRotator;
	deltaRotation.Yaw = value * deltaTime * turnRate;

	AddActorLocalRotation(deltaRotation,true);
	
}

void ATank::handleDestruction()
{

	Super::handleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

}
