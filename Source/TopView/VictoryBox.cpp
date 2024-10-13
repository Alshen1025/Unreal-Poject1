// Fill out your copyright notice in the Description page of Project Settings.

#include "TopViewCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DodgeballPlayerController.h"
#include "GameInterface.h"
#include "VictoryBox.h"
#include "VictoryComponent.h"

// Sets default values
AVictoryBox::AVictoryBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);

	//boxextent 속성을 모든 축에 대해 60유닛으로 설정(크기가 2배가 됨)
	CollisionBox->SetBoxExtent(FVector(60.0f, 60.0f, 60.0f));
	//z축 상대위치 조정
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));

	//함수를 OnComponentbeginOverlap이벤트에 바인딩
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AVictoryBox::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AVictoryBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVictoryBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AVictoryBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("overlaped!"))
	if (Cast<ATopViewCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("player!"))
		ATopViewCharacter* Player = Cast< ATopViewCharacter>(OtherActor);
		UVictoryComponent* VictoryComponent = Player->FindComponentByClass<UVictoryComponent>();
		if (VictoryComponent != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("VictoryComponent != nullptr"))
			VictoryComponent->Victory();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("VictoryComponent == nullptr"))
		}
	}
}