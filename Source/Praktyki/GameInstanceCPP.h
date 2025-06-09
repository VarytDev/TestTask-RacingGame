// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceCPP.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGameModeType : uint8
{
	Practice,
	Race
};

UCLASS()
class PRAKTYKI_API UGameInstanceCPP : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	EGameModeType SelectedMode = EGameModeType::Practice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TimeRestriction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LapLimit;
};
