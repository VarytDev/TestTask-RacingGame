// Copyright 2025 Teyon. All Rights Reserved.


#include "CarPawn.h"

// Sets default values
ACarPawn::ACarPawn()
{
	CarSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal_Mesh"));
	SetRootComponent(CarSkeletalMeshComponent);
	
	MainBodyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main_Body"));
	MainBodyComponent->SetupAttachment(CarSkeletalMeshComponent);
	
	DoorRightComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door_Right"));
	DoorRightComponent->SetupAttachment(CarSkeletalMeshComponent);
	
	DoorLeftComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door_Left"));
	DoorLeftComponent->SetupAttachment(CarSkeletalMeshComponent);
	
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACarPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

#if WITH_EDITOR
void ACarPawn::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ACarPawn, CarSkeletalMesh) && CarSkeletalMesh)
	{
		VehicleName = CarSkeletalMesh->GetName().RightChop(3);
		VehicleName = VehicleName.Replace(TEXT("-"), TEXT("_"));

		if (!CarSkeletalMeshComponent)
		{
			UE_LOG(LogTemp, Error, TEXT("CarSkeletalMeshComponent is null in PostEditChangeProperty!"));
			return;
		}
	
		CarSkeletalMeshComponent->SetSkeletalMesh(CarSkeletalMesh);
		SetupStaticMeshes();
	}
}

void ACarPawn::SetupStaticMeshes() const
{
	SetupMeshComponent(*MainBodyComponent, FName(VehicleName));
	SetupMeshComponent(*DoorRightComponent, TEXT("door_right"));
	SetupMeshComponent(*DoorLeftComponent, TEXT("door_left"));
}

void ACarPawn::SetupMeshComponent(UStaticMeshComponent& MeshComponent, const FName BoneName) const
{
	FStringFormatNamedArguments Args;
	Args.Add(TEXT("vehicle"), VehicleName);
	Args.Add(TEXT("component"), MeshComponent.GetName());
	
	MeshComponent.SetupAttachment(CarSkeletalMeshComponent, BoneName);

	const FString MeshPath = FString::Format(TEXT("/Game/Vehicles/{vehicle}/SM_{vehicle}_{component}.SM_{vehicle}_{component}"), Args);

	if (UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, *MeshPath))
	{
		MeshComponent.SetStaticMesh(Mesh);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh: %s"), *MeshPath);
	}
}
#endif

