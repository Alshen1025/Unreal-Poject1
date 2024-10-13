// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "HealthInterface.h"
#include "GameFramework/Actor.h"

// Sets default values
AHealthComponent::AHealthComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthComponent::LoseHealth(float Damage)
{
	Health -= Damage;
	if (Health <= 0.f)
	{
		Health = 0.f;
		if (GetOwner()->Implements<UHealthInterface>())
		{
			IHealthInterface::Execute_OnDeath(GetOwner());
		}
	}
}

