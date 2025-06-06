// Copyright 2025 Teyon. All Rights Reserved.

#include "ArcadeDriveComponent.h"

UArcadeDriveComponent::UArcadeDriveComponent(): Velocity(0.0f)
{
	PrimaryComponentTick.bCanEverTick = false;

	if (!SkeletalMesh) return;

	//Make sure skeletal mesh properties are correct
	SkeletalMesh->SetSimulatePhysics(true);
	SkeletalMesh->SetEnableGravity(true);
	SkeletalMesh->SetMassOverrideInKg(NAME_None, 1500.0f);
}

void UArcadeDriveComponent::MoveForward(const float Value)
{
	ForwardInput = FMath::Clamp(Value, -1.0f, 1.0f);
}

void UArcadeDriveComponent::Turn(const float Value)
{
	TurnInput = FMath::Clamp(Value, -1.0f, 1.0f);
}

void UArcadeDriveComponent::TickUpdate(float DeltaTime)
{
	FVector Forward = GetOwner()->GetActorForwardVector();
	
	if (FMath::Abs(ForwardInput) > KINDA_SMALL_NUMBER)
	{
		Velocity += Forward * ForwardInput * Acceleration * DeltaTime;
		Velocity = Velocity.GetClampedToMaxSize(MaxSpeed);
	}
	else
	{
		// TODO make friction variable, and account for engine breaking?
		Velocity *= 0.98f;
	}

	if (FMath::Abs(TurnInput) > KINDA_SMALL_NUMBER)
	{
		const float TurnAmount = TurnInput * TurnSpeed * DeltaTime;
		FRotator NewRotation = GetOwner()->GetActorRotation();
		NewRotation.Yaw += TurnAmount;
		GetOwner()->SetActorRotation(NewRotation);
	}

	//TODO Handle it so that vehicle can be reversed but velocity remains 
	Velocity = Forward * Velocity.Length();
	GetOwner()->AddActorWorldOffset(Velocity * DeltaTime, true);
}

