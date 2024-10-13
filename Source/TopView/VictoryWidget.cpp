// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DodgeballPlayerController.h"


void UVictoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UE_LOG(LogTemp, Warning, TEXT("Widget initialized"))
		if (RestartButton != nullptr)
		{
			RestartButton->OnClicked.AddDynamic(this, &UVictoryWidget::OnRestartClicked);
			UE_LOG(LogTemp, Warning, TEXT("Button Click Event Connected"))

				ExitButton->OnClicked.AddDynamic(this, &UVictoryWidget::OnExitClicked);
			UE_LOG(LogTemp, Warning, TEXT("Button Click Event Connected"))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("RestartButton is null"));
		}
}
void UVictoryWidget::OnRestartClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Victory button clicked!"));
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is true"));
		RestartButton->SetKeyboardFocus();
		PlayerController->HideVictoryWidget();
	}
	//재시작
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void UVictoryWidget::OnExitClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("EXit button clicked!"));
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is true"));
		RestartButton->SetKeyboardFocus();
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
	}
	//재시작
}