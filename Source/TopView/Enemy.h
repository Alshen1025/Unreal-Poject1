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

	//적 캐릭터가 이번 프레임에 플레이어를 볼 수 있는지 여부
	bool bCanSeePlayer = false;

	//이전 프레임에 볼 수 있는가
	bool bPreviousCanSeePlayer = false;


	//타이머 기능 속성 추가
	FTimerHandle ThrowTimerHandle;
	//닷지볼 던지는 쿨타임
	float ThrowingInterval = 2.f;
	//타이머 루프 전 대기시간(딜레이)
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
