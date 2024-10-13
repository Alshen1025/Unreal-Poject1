// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballFunctionLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

bool UDodgeballFunctionLibrary::CanSeeActor(const UWorld* world, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoreActors)
{
	//TargetActor가 nullptr인지 확인
	if (TargetActor == nullptr) return false;

	//라인 트레이스의 결과와 관련한 데이터 저장 변수, 언리얼에서 FHitResult라는 내장 타입 제공
	FHitResult Hit;

	//라인 트레이스의 시작과 끝, 시작은 SightSource에서 시작
	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();

	UE_LOG(LogTemp, Warning, TEXT(""), *Start.ToString());

	// 시야 판단을 위해 비교할 트레이스 채널
	//프로젝트 세팅의 콜리전에서 추가한 EnemySight 트레이스 채널, DefaultEngine.ini파일을
	//살펴보면 트레이스 채널이 나옴
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel2;

	//FCollisionQueryParams 타입 사용시 라인 트레이스에 더 많은 옵션을 사용할 수 있음
	FCollisionQueryParams QueryParams;
	//라인 트레이스를 실행하는 액터를 무시함
	QueryParams.AddIgnoredActors(IgnoreActors);
	//대상 액터를 무시할 목록에 추가

	// 라인 트레이스 실행하기
	world->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	//라인트레이스 보기
	DrawDebugLine(world, Start, End, FColor::Red);


	//타겟액터까지 라인트레이스를 실행해서 중간에 막히면 라인트레이스가 true이므로 부정
	//연산자로 false를 리턴하도록 함
	return !Hit.bBlockingHit;
}