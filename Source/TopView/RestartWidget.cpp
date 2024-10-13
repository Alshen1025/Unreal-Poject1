// Fill out your copyright notice in the Description page of Project Settings.
#include "CoreMinimal.h"

#include "RestartWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DodgeballPlayerController.h"


void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UE_LOG(LogTemp, Warning, TEXT("Widget initialized"))
	if (RestartButton != nullptr)
	{
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::OnRestartClicked);
		UE_LOG(LogTemp, Warning, TEXT("Button Click Event Connected"))

		ExitButton->OnClicked.AddDynamic(this, &URestartWidget::OnExitClicked);
		UE_LOG(LogTemp, Warning, TEXT("Button Click Event Connected"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RestartButton is null"));
	}
}

void URestartWidget::OnRestartClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Restart button clicked!"));
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is true"));
		RestartButton->SetKeyboardFocus();
		PlayerController->HideRestartWidget();
	}
	//�����
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void URestartWidget::OnExitClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("EXit button clicked!"));
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is true"));
		RestartButton->SetKeyboardFocus();
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
	}
	//�����
}