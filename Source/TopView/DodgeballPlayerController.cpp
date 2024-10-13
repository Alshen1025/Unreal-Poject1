// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetSystemLibrary.h"
#include "DodgeballPlayerController.h"
#include "RestartWidget.h"
#include "HUDWidget.h"
#include "VictoryWidget.h"

void ADodgeballPlayerController::ShowRestartWidget()
{
	
	if (BP_Restart != nullptr)
	{
		//게임 일시 정지
		SetPause(true);
		//UI만 입력되게 하고 마우스 커서를 true로 함
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;

		//위젯 생성 후 전달, 화면에 추가
		RestartWidget = CreateWidget<URestartWidget>(this, BP_Restart);
		RestartWidget->AddToViewport();
	}
}

void ADodgeballPlayerController::HideRestartWidget()
{
	//위젯 제거 및 삭제
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();
	//게임 정지 해제
	SetPause(false);

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
void ADodgeballPlayerController::UpdateHealthPercent(float HealthPercent)
{
	if (HUDWidget != nullptr)
	{
		HUDWidget->UpdateHealthPercent(HealthPercent);
	}
}
void ADodgeballPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (BP_HUDWidget != nullptr)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
}

void ADodgeballPlayerController::ShowVictoryWidget()
{
	if (BP_Restart != nullptr)
	{
		//게임 일시 정지
		SetPause(true);
		//UI만 입력되게 하고 마우스 커서를 true로 함
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;

		//위젯 생성 후 전달, 화면에 추가
		VictoryWidget = CreateWidget<UVictoryWidget>(this, BP_Victory);
		VictoryWidget->AddToViewport();
	}
}
void ADodgeballPlayerController::HideVictoryWidget()
{
	//위젯 제거 및 삭제
	VictoryWidget->RemoveFromParent();
	VictoryWidget->Destruct();
	//게임 정지 해제
	SetPause(false);

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
