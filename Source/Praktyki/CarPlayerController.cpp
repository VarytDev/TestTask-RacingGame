// Copyright 2025 Teyon. All Rights Reserved.


#include "CarPlayerController.h"

#include "ArcadeDriveComponent.h"
#include "Checkpoint.h"
#include "CheckpointManager.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

void ACarPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentLapTime += DeltaSeconds;
}

void ACarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	if (ACheckpointManager* Manager = Cast<ACheckpointManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACheckpointManager::StaticClass())))
	{
		Checkpoints = Manager->Checkpoints;

		for (auto Checkpoint : Checkpoints)
		{
			Checkpoint->OnOverlap.BindUObject(this, &ACarPlayerController::HandleOverlapingCheckpoint);
			Checkpoint->WaypointMesh->SetVisibility(false);
		}

		const int NextIndex = GetNextCheckpointIndex();
		Checkpoints[NextIndex]->WaypointMesh->SetVisibility(true);
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

void ACarPlayerController::Destroyed()
{
	Super::Destroyed();

	for (auto Checkpoint : Checkpoints)
	{
		Checkpoint->OnOverlap.Unbind();
	}
}

void ACarPlayerController::HandleOverlapingCheckpoint(ACheckpoint& Checkpoint)
{
	if (Checkpoints.Num() < 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Checkpoints array is empty"));
		return;
	}

	int NextIndex = GetNextCheckpointIndex();
	if (NextIndex > Checkpoints.Num() - 1)
	{
		NextIndex = 0;
	}
	
	if (Checkpoints[NextIndex] == &Checkpoint)
	{
		CurrentCheckpointDisplay = NextIndex + 1;
		CurrentCheckpoint = &Checkpoint;
		CurrentCheckpoint->WaypointMesh->SetVisibility(false);

		NextIndex = GetNextCheckpointIndex();
		
		if (NextIndex > Checkpoints.Num() - 1) //Last index is length - 1
		{
			CurrentCheckpointDisplay = 0;
			NextIndex = 0;
			HandleFinishingLap();
		}
		
		Checkpoints[NextIndex]->WaypointMesh->SetVisibility(true);
	}
}

void ACarPlayerController::HandleFinishingLap()
{
	if (CurrentLap == 0 || CurrentLapTime < BestLapTime)
	{
		BestLapTime = CurrentLapTime;
	}

	CurrentLapTime = 0;
	CurrentLap++;

	OnLapCompleted.ExecuteIfBound(CurrentLap, BestLapTime);
}

int ACarPlayerController::GetNextCheckpointIndex() const
{
	if (CurrentCheckpoint == nullptr) return 0;
	return Checkpoints.Find(CurrentCheckpoint) + 1;
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
