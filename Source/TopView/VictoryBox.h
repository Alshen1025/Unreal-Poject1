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
	//�Ķ���� : �������� �߻��� ������Ʈ �� �� ���Ϳ� ���Ե� ������Ʈ, �ٸ� ����, �ٸ� ������ ������Ʈ, ������Ʈ �ε���(����ƽ �޽� ������Ʈ�� ����), �������� ����Ʈ���̽��κ��� ���۵Ǿ����� ����
	//���� Ʈ���̽� ��� ������
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	//OnEndOverlap�̺�Ʈ
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
