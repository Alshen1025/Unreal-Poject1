// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DodgeballPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOPVIEW_API ADodgeballPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URestartWidget> BP_Restart;
	void ShowRestartWidget();
	void HideRestartWidget();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;
	void UpdateHealthPercent(float HealthPercent);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UVictoryWidget> BP_Victory;
	void ShowVictoryWidget();
	void HideVictoryWidget();
	
private:

	UPROPERTY()
	class URestartWidget* RestartWidget;

	UPROPERTY()
	class UHUDWidget* HUDWidget;

	UPROPERTY()
	class UVictoryWidget* VictoryWidget;



protected:
	virtual void BeginPlay() override;
	
};
