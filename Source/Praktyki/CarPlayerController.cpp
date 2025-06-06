// Copyright 2025 Teyon. All Rights Reserved.


#include "CarPlayerController.h"

#include "ArcadeDriveComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

void ACarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ACarPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(DriveInputAction, ETriggerEvent::Triggered, this, &ACarPlayerController::HandleMoveInput);
		EnhancedInput->BindAction(DriveInputAction, ETriggerEvent::Completed, this, &ACarPlayerController::HandleMoveInput);
		EnhancedInput->BindAction(DriveInputAction, ETriggerEvent::Canceled, this, &ACarPlayerController::HandleMoveInput);
	}
}

void ACarPlayerController::HandleMoveInput(const FInputActionInstance& Instance)
{
	FVector2D Move = Instance.GetValue().Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn())
	{
		if (UArcadeDriveComponent* Drive = ControlledPawn->FindComponentByClass<UArcadeDriveComponent>())
		{
			Drive->MoveForward(Move.Y);
			Drive->Turn(Move.X);
		}
	}
}