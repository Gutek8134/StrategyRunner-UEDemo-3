// Copyright Epic Games, Inc. All Rights Reserved.

#include "StrategyRunnerGameMode.h"
#include "StrategyRunnerPlayerController.h"
#include "StrategyRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStrategyRunnerGameMode::AStrategyRunnerGameMode()
{
	DefaultPawnClass = ConstructorHelpers::FClassFinder<APawn>(TEXT("/Game/Runner/RunningCharacter")).Class;
}