// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TOPVIEW_API AEnemy : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LookAt, meta = (AllowPrivateAccess = "true"))
	class ULookAtActorComponent* LookAtActorComponent;

	

public:
	// Sets default values for this character's properties
	AEnemy();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//bool CanSeeActor(AActor* TargetActor);

	//�� ĳ���Ͱ� �̹� �����ӿ� �÷��̾ �� �� �ִ��� ����
	bool bCanSeePlayer = false;

	//���� �����ӿ� �� �� �ִ°�
	bool bPreviousCanSeePlayer = false;


	//Ÿ�̸� ��� �Ӽ� �߰�
	FTimerHandle ThrowTimerHandle;
	//������ ������ ��Ÿ��
	float ThrowingInterval = 2.f;
	//Ÿ�̸� ���� �� ���ð�(������)
	float ThrowingDelay = 0.5f;

	void ThrowDodgeball();

	//dodgeball
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Dodgeball)
	TSubclassOf<class ADodgeball> DodgeballClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
