// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopViewCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Health.h"
#include "VictoryComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "DodgeballPlayerController.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ATopViewCharacter

ATopViewCharacter::ATopViewCharacter()
{
	//ĸ�� ������Ʈ
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 900.0f;
	//ī�޶� �÷��̾ ������ ������ ������
	CameraBoom->SetRelativeRotation(FRotator(-70.0f, 0.f, 0.f));
	CameraBoom->bUsePawnControlRotation = false; 
	//ĳ������ ȸ���� ���� ī�޶��� ȸ���� ������� �ʵ��� ����
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;

	//ī�޻�
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	HealthComponent = CreateDefaultSubobject<UHealth>(TEXT("HealthComponent"));
	VictoryComponent = CreateDefaultSubobject<UVictoryComponent>(TEXT("VictoryComponent"));

}

void ATopViewCharacter::BeginPlay()
{ 
	Super::BeginPlay();
}



void ATopViewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedSubsystem->AddMappingContext(IC_Character, 1);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		

		// Moving
		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATopViewCharacter::Move);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATopViewCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
void ATopViewCharacter::OnDeath_Implementation()
{
	//��Ʈ�ѷ����� ���� �Լ� ȣ��
	UE_LOG(LogTemp, Warning, TEXT("Dead!"));
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetController());

	//���⼭ ���� �߻�(���ǹ����� ���� ���� = PlayerControll�� nullptr��
	if (PlayerController != nullptr)
	{
		PlayerController->ShowRestartWidget();
		
	}
}

void ATopViewCharacter::OnTakeDamage_Implementation()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateHealthPercent(HealthComponent->GetHealthPercent());
	}
}

void ATopViewCharacter::PlayerVictory_Implementation()
{
	ADodgeballPlayerController* PlayerController = Cast<ADodgeballPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->ShowVictoryWidget();

	}
}
