// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "VictoryBox.generated.h"

UCLASS()
class TOPVIEW_API AVictoryBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVictoryBox();
	//파라미터 : 오버랩이 발생한 컴포넌트 중 이 액터에 포함된 컴포넌트, 다른 액터, 다른 액터의 컴포넌트, 컴포넌트 인덱스(스태틱 메시 컴포넌트에 유용), 오버랩이 스윕트레이스로부터 시작되었는지 여부
	//스윕 트레이스 결과 데이터
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	//OnEndOverlap이벤트
	//void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VictoryBox, meta = (AllowPrivatrAccess = "true"))
	class USceneComponent* RootScene;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VictoryBox, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;
};
