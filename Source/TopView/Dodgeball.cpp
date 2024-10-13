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
	// radius설정
	SphereComponent->SetSphereRadius(35.f);
	//콜리전 프리셋 설정하고 피직스 시뮬레이션 옵션 활성화
	SphereComponent->SetCollisionProfileName(FName("DodgeBall"));
	SphereComponent->SetSimulatePhysics(true);
	//시뮬레이션 HIt이벤트 발생시킴
	SphereComponent->SetNotifyRigidBodyCollision(true);

	//Onhit이벤트 받기
	SphereComponent->OnComponentHit.AddDynamic(this, &ADodgeball::OnHit);

	//sphere컴포넌트를 root컴포넌트로 설정하지 않으면 콜리전이 제대로 동작하지 않을 수있다
	//왜?
	RootComponent = SphereComponent;

	//ProjectileMovementComponenet 오브젝트 생성
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
}
// Called when the game starts or when spawned
void ADodgeball::BeginPlay()
{
	Super::BeginPlay();
	//모든 액터가 갖는 Lifespan속성, 생성후나 게임 시작 후 지정된 시간이 지나면 파괴됨
	SetLifeSpan(2.0f);
	
}

// Called every frame
void ADodgeball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADodgeball::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//벽에 튕기는 힘이 클때만 출력
	
	//충돌한 otheractor를 ATopViewCharacter(플레이어 캐릭터)로 형변환해서 맞으면 destroy. TopViewCharacter.h헤더 추가
	ATopViewCharacter* Player = Cast< ATopViewCharacter>(OtherActor);
	if (BounceSound != nullptr && NormalImpulse.Size() > 5000.0f)
	{
		//플레이어에게 충돌할때도 출력되는 거 수정
		if (Player == nullptr)
		{
			//파라미터 WorldContext, SoundBase속성, 소리의 진원지, 볼륨 속성, 사운드의 피치, 사운드 몇초부터 재생할건지, Attenuation
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
			//world오브잭트, uparticlessystem속성, 액터의 Ftransform
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, GetActorTransform());
		}
		if (BounceSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
			

		}
		Destroy();
	}
}

