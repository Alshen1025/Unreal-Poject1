// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HealthInterface.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UHealth::LoseHealth(float Damage)
{
	Health -= Damage;
	if (GetOwner()->Implements<UHealthInterface>())
	{
		IHealthInterface::Execute_OnTakeDamage(GetOwner());
	}

	if (Health <= 0.f)
	{
		Health = 0.f;
		
		//������Ʈ�� Ư�� �������̽��� �����ߴ��� Ȯ�� �� �� ������Ʈ�� implementȮ��
		if (GetOwner()->Implements<UHealthInterface>())
		{
			IHealthInterface::Execute_OnDeath(GetOwner());
		}
	}
}

