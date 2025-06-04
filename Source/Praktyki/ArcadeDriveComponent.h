// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArcadeDriveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRAKTYKI_API UArcadeDriveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UArcadeDriveComponent();

	void MoveForward(float Value);
	void Turn(float Value);

	void TickUpdate(float DeltaTime);

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;
	
	UPROPERTY(EditAnywhere)
	float Acceleration = 2000.f;

	UPROPERTY(EditAnywhere)
	float TurnSpeed = 100.f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 4000.f;

private:
	FVector Velocity;
	float ForwardInput = 0.f;
	float TurnInput = 0.f;
};
