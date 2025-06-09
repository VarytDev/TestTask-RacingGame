// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint.h"
#include "GameFramework/Actor.h"
#include "CheckpointManager.generated.h"

UCLASS()
class PRAKTYKI_API ACheckpointManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointManager();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Checkpoints")
	TArray<ACheckpoint*> Checkpoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
