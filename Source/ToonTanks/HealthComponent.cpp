// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	health = maxHealth;

	GetOwner() -> OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::damageTaken);

	toonTanksGameModeClass = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::damageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	health -= Damage;

	if (health  <= 0.f && toonTanksGameModeClass)
	{
		toonTanksGameModeClass -> actorDied(DamagedActor);
	}

}

