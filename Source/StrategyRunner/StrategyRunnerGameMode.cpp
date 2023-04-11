// Copyright Epic Games, Inc. All Rights Reserved.

#include "StrategyRunnerGameMode.h"
#include "StrategyRunnerPlayerController.h"
#include "StrategyRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStrategyRunnerGameMode::AStrategyRunnerGameMode()
{
	DefaultPawnClass = ConstructorHelpers::FClassFinder<ACharacter>(TEXT("/Game/Runner/RunningCharacter")).Class;
	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}