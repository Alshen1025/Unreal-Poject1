// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryComponent.h"
#include "GameInterface.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UVictoryComponent::UVictoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVictoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVictoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UVictoryComponent::Victory()
{
	if (GetOwner()->Implements<UGameInterface>())
	{
		IGameInterface::Execute_PlayerVictory(GetOwner());
	}
}
