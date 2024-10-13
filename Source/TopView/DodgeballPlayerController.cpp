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
		//���� �Ͻ� ����
		SetPause(true);
		//UI�� �Էµǰ� �ϰ� ���콺 Ŀ���� true�� ��
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;

		//���� ���� �� ����, ȭ�鿡 �߰�
		RestartWidget = CreateWidget<URestartWidget>(this, BP_Restart);
		RestartWidget->AddToViewport();
	}
}

void ADodgeballPlayerController::HideRestartWidget()
{
	//���� ���� �� ����
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();
	//���� ���� ����
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
		//���� �Ͻ� ����
		SetPause(true);
		//UI�� �Էµǰ� �ϰ� ���콺 Ŀ���� true�� ��
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;

		//���� ���� �� ����, ȭ�鿡 �߰�
		VictoryWidget = CreateWidget<UVictoryWidget>(this, BP_Victory);
		VictoryWidget->AddToViewport();
	}
}
void ADodgeballPlayerController::HideVictoryWidget()
{
	//���� ���� �� ����
	VictoryWidget->RemoveFromParent();
	VictoryWidget->Destruct();
	//���� ���� ����
	SetPause(false);

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
