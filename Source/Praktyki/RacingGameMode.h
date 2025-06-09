// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CarPlayerController.h"
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
	virtual void Destroyed() override;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool IsTimeRestricted;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int TimeRestriction;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool IsLapLimited;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int LapLimit;

protected:
	void HandleLapCompleted(int Lap, float BestTime) const;
	void ShowRaceEndScreen(FText BestTime) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WidgetClass;
	
	ACarPlayerController* PC;
	FTimerHandle TimerHandle;
};
