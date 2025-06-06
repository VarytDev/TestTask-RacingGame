// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "CarPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API ACarPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere)
	UInputAction* DriveInputAction;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void HandleMoveInput(const FInputActionInstance& Instance);
};
