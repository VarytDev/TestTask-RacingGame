// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RacingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API ARacingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool IsTimeRestricted;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int TimeRestriction;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool IsLapLimited;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int LapLimit;
};
