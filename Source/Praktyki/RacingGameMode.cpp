// Copyright 2025 Teyon. All Rights Reserved.


#include "RacingGameMode.h"

#include "CarPlayerController.h"
#include "GameInstanceCPP.h"
#include "RaceFinishedWidget_CPP.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void ARacingGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (const UGameInstanceCPP* GI = Cast<UGameInstanceCPP>(GetWorld()->GetGameInstance()))
	{
		switch (GI->SelectedMode)
		{
		default:
		case EGameModeType::Practice:
			IsTimeRestricted = false;
			IsLapLimited = false;
			break;
		case EGameModeType::Race:
			IsLapLimited = true;
			IsTimeRestricted = true;
			LapLimit = GI->LapLimit;
			TimeRestriction = GI->TimeRestriction;
			break;
		}
	}

	PC = Cast<ACarPlayerController>(GetWorld()->GetFirstPlayerController());

	if (PC)
	{
		PC->OnLapCompleted.BindUObject(this, &ARacingGameMode::HandleLapCompleted);
	}
	
	if (IsTimeRestricted)
	{
		GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		[this]()
		{
			ShowRaceEndScreen(FText::FromString("DNF"));
		},
		TimeRestriction,
		false
	);
	}
}

void ARacingGameMode::Destroyed()
{
	Super::Destroyed();

	if (PC)
	{
		PC->OnLapCompleted.Unbind();
	}
}

void ARacingGameMode::HandleLapCompleted(int Lap, float BestTime) const
{
	if (!IsLapLimited) return;
	//TODO Should make static function to convert seconds to MM:SS time format
	const int Minutes = BestTime / 60;
	const int Seconds = BestTime - Minutes * 60;
	
	FFormatNamedArguments Args;
	Args.Add(TEXT("Minutes"), FText::AsNumber(Minutes));
	Args.Add(TEXT("Seconds"), FText::AsNumber(Seconds));
	
	FText FormattedTime = FText::Format(FText::FromString("{Minutes}:{Seconds}"), Args);
	
	if (Lap >= LapLimit) ShowRaceEndScreen(FText::AsNumber(BestTime));
}

void ARacingGameMode::ShowRaceEndScreen(FText BestTime) const
{
	if (WidgetClass)
	{
		if (URaceFinishedWidget_CPP* Widget = CreateWidget<URaceFinishedWidget_CPP>(GetWorld(), WidgetClass))
		{
			Widget->AddToViewport();
			Widget->InitializeWindow(BestTime);

			PC->bShowMouseCursor = true;
			FInputModeUIOnly InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PC->SetInputMode(InputMode);
		}
	}
}
