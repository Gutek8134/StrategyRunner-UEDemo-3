// Copyright Epic Games, Inc. All Rights Reserved.

#include "StrategyRunnerPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "StrategyRunnerCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AStrategyRunnerPlayerController::AStrategyRunnerPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AStrategyRunnerPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AStrategyRunnerPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AStrategyRunnerPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AStrategyRunnerPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AStrategyRunnerPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AStrategyRunnerPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AStrategyRunnerPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AStrategyRunnerPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AStrategyRunnerPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AStrategyRunnerPlayerController::OnTouchReleased);
	}
}

void AStrategyRunnerPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AStrategyRunnerPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AStrategyRunnerPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AStrategyRunnerPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AStrategyRunnerPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
