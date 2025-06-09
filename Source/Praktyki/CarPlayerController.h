// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "CarPlayerController.generated.h"

DECLARE_DELEGATE_TwoParams(FOnLapCompleted, int, float);

class ACheckpoint;
/**
 * 
 */
UCLASS()
class PRAKTYKI_API ACarPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<ACheckpoint*> Checkpoints;
	
	UPROPERTY(BlueprintReadOnly)
	int CurrentLap = 0;

	UPROPERTY(BlueprintReadOnly)
	int CurrentCheckpointDisplay = 0;

	UPROPERTY(BlueprintReadOnly)
	float CurrentLapTime = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float BestLapTime = 0.0f;

	FOnLapCompleted OnLapCompleted;
	
protected:
	UPROPERTY(VisibleAnywhere)
	ACheckpoint* CurrentCheckpoint = nullptr;
	
	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere)
	UInputAction* DriveInputAction;

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Destroyed() override;
	void HandleMoveInput(const FInputActionInstance& Instance);
	void HandleOverlapingCheckpoint(ACheckpoint& Checkpoint);
	void HandleFinishingLap();
	int GetNextCheckpointIndex() const;
};
