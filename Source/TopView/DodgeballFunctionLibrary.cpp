// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballFunctionLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

bool UDodgeballFunctionLibrary::CanSeeActor(const UWorld* world, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoreActors)
{
	//TargetActor�� nullptr���� Ȯ��
	if (TargetActor == nullptr) return false;

	//���� Ʈ���̽��� ����� ������ ������ ���� ����, �𸮾󿡼� FHitResult��� ���� Ÿ�� ����
	FHitResult Hit;

	//���� Ʈ���̽��� ���۰� ��, ������ SightSource���� ����
	FVector Start = Location;
	FVector End = TargetActor->GetActorLocation();

	UE_LOG(LogTemp, Warning, TEXT(""), *Start.ToString());

	// �þ� �Ǵ��� ���� ���� Ʈ���̽� ä��
	//������Ʈ ������ �ݸ������� �߰��� EnemySight Ʈ���̽� ä��, DefaultEngine.ini������
	//���캸�� Ʈ���̽� ä���� ����
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel2;

	//FCollisionQueryParams Ÿ�� ���� ���� Ʈ���̽��� �� ���� �ɼ��� ����� �� ����
	FCollisionQueryParams QueryParams;
	//���� Ʈ���̽��� �����ϴ� ���͸� ������
	QueryParams.AddIgnoredActors(IgnoreActors);
	//��� ���͸� ������ ��Ͽ� �߰�

	// ���� Ʈ���̽� �����ϱ�
	world->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	//����Ʈ���̽� ����
	DrawDebugLine(world, Start, End, FColor::Red);


	//Ÿ�پ��ͱ��� ����Ʈ���̽��� �����ؼ� �߰��� ������ ����Ʈ���̽��� true�̹Ƿ� ����
	//�����ڷ� false�� �����ϵ��� ��
	return !Hit.bBlockingHit;
}