// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtActorComponent.h"
#include "DodgeballFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
ULookAtActorComponent::ULookAtActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULookAtActorComponent::BeginPlay()
{

	Super::BeginPlay();

	

	// ...
	
}


// Called every frame
void ULookAtActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bCanSeeTarget = LookAtActor();
	// ...
}

bool ULookAtActorComponent::LookAtActor()
{
	//TargetActor확인
	if (TargetActor == nullptr) return false;
	//대상 액터를 볼 수 있는지 확인
	TArray<const AActor*> IgnoreActors = { GetOwner(), TargetActor};
	if (UDodgeballFunctionLibrary::CanSeeActor(GetWorld(), GetComponentLocation(), TargetActor, IgnoreActors))
	{
		FVector Start = GetOwner()->GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		//FindLookAtRotation은 시작지점의 물체가 끝 지점의 물체를 바라보기위한 회전을 구하는 함수
		// #include "Kismet/KismetMathLibrary.h"추가해야함
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		//적 캐릭터의 회전을 구한 값과 동일하게 설정
		GetOwner()->SetActorRotation(LookAtRotation);
		//볼 수 있으면 true 반환
		return true;
	}
	return false;
}
