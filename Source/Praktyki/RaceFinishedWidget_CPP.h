// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RaceFinishedWidget_CPP.generated.h"

/**
 * 
 */
UCLASS()
class PRAKTYKI_API URaceFinishedWidget_CPP : public UUserWidget
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitializeWindow(const FText& BestTimeText);

	virtual void InitializeWindow_Implementation(const FText& BestTimeText);
};
