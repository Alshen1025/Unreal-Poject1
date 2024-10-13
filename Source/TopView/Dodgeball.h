// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Dodgeball.generated.h"

UCLASS()
class TOPVIEW_API ADodgeball : public AActor
{
	GENERATED_BODY()

private:
	//콜리전 컴포넌트 추가를 위해 sphere component추가
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = DodgeBall, meta = (AllowPrivateAccess = true))
	class USphereComponent* SphereComponent;

	//프로젝타일 무브먼트 = 발사체에 동작을 부여하기위해 사용
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = Dodgeball, meta = (AllowPrivateAccess ="true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* BounceSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundAttenuation* BounceSoundAttenuation;

	UPROPERTY(EditAnywhere, Category = Particles)
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = Sound)
	class USoundBase* DamageSound;
	
public:	
	// Sets default values for this actor's properties
	ADodgeball();

	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const
	{
		return ProjectileMovement;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	//HitComp 충돌이 발생한 컴포넌트 중 이 액터애 포함된 컴포넌트, OtherActor 충돌에 관여한 다른 액터, OtherComp다른 액터의 컴포넌트, NormalImpulse다른 물체와 부딫힌 후 움직일 벡터
	//Hit 데이터
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


};
