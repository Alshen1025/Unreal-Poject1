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
	//�ݸ��� ������Ʈ �߰��� ���� sphere component�߰�
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = DodgeBall, meta = (AllowPrivateAccess = true))
	class USphereComponent* SphereComponent;

	//������Ÿ�� �����Ʈ = �߻�ü�� ������ �ο��ϱ����� ���
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
	//HitComp �浹�� �߻��� ������Ʈ �� �� ���;� ���Ե� ������Ʈ, OtherActor �浹�� ������ �ٸ� ����, OtherComp�ٸ� ������ ������Ʈ, NormalImpulse�ٸ� ��ü�� �΋H�� �� ������ ����
	//Hit ������
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


};
