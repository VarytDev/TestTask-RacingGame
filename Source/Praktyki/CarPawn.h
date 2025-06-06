// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ArcadeDriveComponent.h"
#include "GameFramework/Pawn.h"
#include "CarPawn.generated.h"

UCLASS()
class PRAKTYKI_API ACarPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACarPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* CarSkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UArcadeDriveComponent* DriveComponent;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* CarSkeletalMesh;

	//Static Mesh Components

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MainBodyComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CockpitConsoleComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Interior;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* EngineComponents;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* InteriorExteriorWindows;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorRightComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorLeftComponent;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	FString VehicleName;

#if WITH_EDITOR
	void SetupStaticMeshes() const;
	void SetupMeshComponent(UStaticMeshComponent& MeshComponent, FName BoneName) const;
#endif
};
