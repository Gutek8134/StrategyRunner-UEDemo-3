// Copyright Epic Games, Inc. All Rights Reserved.

#include "StrategyRunnerGameMode.h"
#include "StrategyRunnerPlayerController.h"
#include "StrategyRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerState.h"

AStrategyRunnerGameMode::AStrategyRunnerGameMode()
{
	DefaultPawnClass = ConstructorHelpers::FClassFinder<APawn>(TEXT("/Game/Runner/RunningCharacter")).Class;
	PlayerStateClass = ConstructorHelpers::FClassFinder<APlayerState>(TEXT("/Game/Runner/MyPlayerState")).Class; 
}