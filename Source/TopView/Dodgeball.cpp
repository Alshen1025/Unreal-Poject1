// Fill out your copyright notice in the Description page of Project Settings.


#include "Dodgeball.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Health.h"
#include "Kismet/GameplayStatics.h"
#include "TopViewCharacter.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADodgeball::ADodgeball()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	// radius����
	SphereComponent->SetSphereRadius(35.f);
	//�ݸ��� ������ �����ϰ� ������ �ùķ��̼� �ɼ� Ȱ��ȭ
	SphereComponent->SetCollisionProfileName(FName("DodgeBall"));
	SphereComponent->SetSimulatePhysics(true);
	//�ùķ��̼� HIt�̺�Ʈ �߻���Ŵ
	SphereComponent->SetNotifyRigidBodyCollision(true);

	//Onhit�̺�Ʈ �ޱ�
	SphereComponent->OnComponentHit.AddDynamic(this, &ADodgeball::OnHit);

	//sphere������Ʈ�� root������Ʈ�� �������� ������ �ݸ����� ����� �������� ���� ���ִ�
	//��?
	RootComponent = SphereComponent;

	//ProjectileMovementComponenet ������Ʈ ����
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
}
// Called when the game starts or when spawned
void ADodgeball::BeginPlay()
{
	Super::BeginPlay();
	//��� ���Ͱ� ���� Lifespan�Ӽ�, �����ĳ� ���� ���� �� ������ �ð��� ������ �ı���
	SetLifeSpan(2.0f);
	
}

// Called every frame
void ADodgeball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADodgeball::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//���� ƨ��� ���� Ŭ���� ���
	
	//�浹�� otheractor�� ATopViewCharacter(�÷��̾� ĳ����)�� ����ȯ�ؼ� ������ destroy. TopViewCharacter.h��� �߰�
	ATopViewCharacter* Player = Cast< ATopViewCharacter>(OtherActor);
	if (BounceSound != nullptr && NormalImpulse.Size() > 5000.0f)
	{
		//�÷��̾�� �浹�Ҷ��� ��µǴ� �� ����
		if (Player == nullptr)
		{
			//�Ķ���� WorldContext, SoundBase�Ӽ�, �Ҹ��� ������, ���� �Ӽ�, ������ ��ġ, ���� ���ʺ��� ����Ұ���, Attenuation
			//UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation(), 1.0f, 1.0f, 0.0f, BounceSoundAttenuation);
		}
		
	}
	if (Player != nullptr)
	{
		UHealth* HealthComponent = Player->FindComponentByClass<UHealth>();
		if (HealthComponent != nullptr)
		{
			HealthComponent->LoseHealth(Damage);
			
		}
		if (HitParticles != nullptr)
		{
			//world������Ʈ, uparticlessystem�Ӽ�, ������ Ftransform
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorTransform());
		}
		if (BounceSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
			

		}
		Destroy();
	}
}

