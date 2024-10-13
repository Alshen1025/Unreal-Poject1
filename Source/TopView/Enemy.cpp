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

	//SightSource ���� �� ������Ʈ�� ����
	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("Look At Actor Component"));
	LookAtActorComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	//���� �÷��� �ϰ��ִ� ĳ���� ã��
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActorComponent->SetTarget(PlayerCharacter);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//�÷��̾ ���� �����ϴ� ĳ���͸� ���ϱ� ���� GameplayStatic��ü�� ����Ϸ���
	//#include "Kismet/GameplayStatics.h" �߰�

	//�÷��̾ �����ϴ� ĳ���� ���ϱ�Getworld�� �Լ��� � ���� ��ü�� �����ؾ� �ϴ���
	//0�� �÷��̾� �ε���
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	// �����Ӹ��� LookActor �Լ� ����

	//�� ������ �÷��̾� ĳ���͸� �ٶ�
	bCanSeePlayer = LookAtActorComponent->CanSeeTarget();
	//���� ������ ���
	
	//�̹� �����ӿ� �� �� ������ ������ �� �� ���� ���� �� �ݴ븦 �ǵ�
	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			//���ϴ� Ÿ�̸Ӹ� ��Ÿ���� FTimerHandle, ȣ���� �Լ��� ���� ������Ʈ, ȣ���� �Լ�, Ÿ�̸��� ����, �ݺ�����, �ݺ��� �����ϱ� �������� ���ð�
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AEnemy::ThrowDodgeball, ThrowingInterval, true, ThrowingDelay);
		}
		else
		{
			//Ÿ�̸� �ߴ�
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

	//SpawnActor<C++Ŭ���� �̸�>(classreference, spawnlocation, spawnRotation)
	//SpawnActor�� SpawnActorDeffered����(��þ��� ����, ������ ���� ����<-���� �� �߰��� ���� �� ������ ������)
	//�Լ� ȣ���� ��ȯ�� Projectile�̶�� �̸��� ADodgeball*�Ӽ��� ����
	ADodgeball* Projectile = GetWorld()->SpawnActorDeferred<ADodgeball>(DodgeballClass, SpawnTransform);


	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2000.f;
	Projectile->FinishSpawning(SpawnTransform);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

