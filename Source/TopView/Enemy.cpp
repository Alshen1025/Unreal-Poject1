// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Dodgeball.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LookAtActorComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SightSource 생성 후 컴포넌트에 부착
	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("Look At Actor Component"));
	LookAtActorComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	//현재 플레이 하고있는 캐릭터 찾기
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActorComponent->SetTarget(PlayerCharacter);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//플레이어가 현재 제어하는 캐릭터를 구하기 위한 GameplayStatic객체를 사용하려면
	//#include "Kismet/GameplayStatics.h" 추가

	//플레이어가 제어하는 캐릭터 구하기Getworld는 함수가 어떤 월드 객체에 접근해야 하는지
	//0은 플레이어 인덱스
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	// 프레임마다 LookActor 함수 실행

	//매 프레임 플레이어 캐릭터를 바라봄
	bCanSeePlayer = LookAtActorComponent->CanSeeTarget();
	//이전 프레임 결과
	
	//이번 프레임에 볼 수 있으나 이전엔 볼 수 없던 경우와 그 반대를 판독
	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			//원하는 타이머를 나타내는 FTimerHandle, 호출할 함수가 속한 오브젝트, 호출할 함수, 타이머의 간격, 반복여부, 반복을 시작하기 전까지의 대기시간
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AEnemy::ThrowDodgeball, ThrowingInterval, true, ThrowingDelay);
		}
		else
		{
			//타이머 중단
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}
	bPreviousCanSeePlayer = bCanSeePlayer;
}

void AEnemy::ThrowDodgeball()
{
	if (DodgeballClass == nullptr)
	{
		return;
	}
	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistace = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistace);
	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	//SpawnActor<C++클래스 이름>(classreference, spawnlocation, spawnRotation)
	//SpawnActor와 SpawnActorDeffered차이(즉시액터 생성, 지연된 액터 생성<-생성 후 추가로 설정 할 사항이 있으면)
	//함수 호출의 반환값 Projectile이라는 이름의 ADodgeball*속성에 저장
	ADodgeball* Projectile = GetWorld()->SpawnActorDeferred<ADodgeball>(DodgeballClass, SpawnTransform);


	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2000.f;
	Projectile->FinishSpawning(SpawnTransform);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

