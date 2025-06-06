// Copyright 2025 Teyon. All Rights Reserved.


#include "CarPawn.h"

#include "ArcadeDriveComponent.h"

ACarPawn::ACarPawn()
{
	CarSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal_Mesh"));
	SetRootComponent(CarSkeletalMeshComponent);
	
	MainBodyComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main_Body"));
	MainBodyComponent->SetupAttachment(CarSkeletalMeshComponent);

	CockpitConsoleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cockpit_Console"));
	CockpitConsoleComponent->SetupAttachment(MainBodyComponent);

	Interior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interior"));
	Interior->SetupAttachment(MainBodyComponent);

	EngineComponents = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Engine_Components"));
	EngineComponents->SetupAttachment(MainBodyComponent);

	InteriorExteriorWindows = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interior_Exterior_Windows"));
	InteriorExteriorWindows->SetupAttachment(MainBodyComponent);
	
	DoorRightComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door_Right"));
	DoorRightComponent->SetupAttachment(CarSkeletalMeshComponent);
	
	DoorLeftComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door_Left"));
	DoorLeftComponent->SetupAttachment(CarSkeletalMeshComponent);
	
	DriveComponent = CreateDefaultSubobject<UArcadeDriveComponent>(TEXT("DriveComponent"));
	
	PrimaryActorTick.bCanEverTick = true;
}

void ACarPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (DriveComponent) DriveComponent->TickUpdate(DeltaTime);
}

void ACarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//TODO Move that whole editor logic to another class?
#if WITH_EDITOR
void ACarPawn::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (!CarSkeletalMeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("CarSkeletalMeshComponent is null in PostEditChangeProperty!"));
		return;
	}
	
	if (CarSkeletalMesh)
	{
		//Remove SK_ from skeletal mesh name
		VehicleName = CarSkeletalMesh->GetName().RightChop(3);
		//Clear some stupid naming errors
		VehicleName = VehicleName.Replace(TEXT("-"), TEXT("_"));
	
		CarSkeletalMeshComponent->SetSkeletalMesh(CarSkeletalMesh);
		SetupStaticMeshes();
	}
}

void ACarPawn::SetupStaticMeshes() const
{
	SetupMeshComponent(*MainBodyComponent, FName(VehicleName));
	SetupMeshComponent(*CockpitConsoleComponent, FName(VehicleName));
	SetupMeshComponent(*Interior, FName(VehicleName));
	SetupMeshComponent(*EngineComponents, FName(VehicleName));
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

