// Copyright 2025 Teyon. All Rights Reserved.


#include "RacingGameMode.h"
#include "GameInstanceCPP.h"

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
}
