// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "VehicleGame.h"
#include "Player/VehiclePlayerController.h"
#include "Player/VehiclePlayerCameraManager.h"
#include "Track/VehicleTrackPoint.h"
#include "UI/VehicleHUD.h"
#include "VehicleGameState.h"
#include "Pawns/BuggyPawn.h"
#include "Pawns/BmwPawn.h"
#include "Pawns/CoupePawn.h"

AVehiclePlayerController::AVehiclePlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerCameraManagerClass = AVehiclePlayerCameraManager::StaticClass();
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
}

void AVehiclePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// UI input
	FInputActionBinding& ToggleInGameMenuBinding = InputComponent->BindAction("InGameMenu", IE_Pressed, this, &AVehiclePlayerController::OnToggleInGameMenu);

	// return to track
	InputComponent->BindAction("BackOnTrack", IE_Pressed, this, &AVehiclePlayerController::Suicide);

	ToggleInGameMenuBinding.bExecuteWhenPaused = true;
}

float AVehiclePlayerController::GetMinRespawnDelay()
{
	return 0.01f;
}

void AVehiclePlayerController::UnFreeze()
{
	ServerRestartPlayer();
}

void AVehiclePlayerController::OnTrackPointReached(AVehicleTrackPoint* TrackPoint)
{
	LastTrackPoint = TrackPoint;
	StartSpot = TrackPoint;
}

void AVehiclePlayerController::OnToggleInGameMenu()
{
	AVehicleHUD* GameHUD = Cast<AVehicleHUD>(MyHUD);
	if (GameHUD)
	{
		GameHUD->ToggleGameMenu();
	}
}

void AVehiclePlayerController::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	
	DOREPLIFETIME( AVehiclePlayerController, bHandbrakeOverride );
}

bool AVehiclePlayerController::IsHandbrakeForced() const
{
	return bHandbrakeOverride;
}

void AVehiclePlayerController::SetHandbrakeForced(bool bNewForced)
{
	bHandbrakeOverride = bNewForced;
}

void AVehiclePlayerController::Suicide()
{
	if (IsInState(NAME_Playing))
	{
		ServerSuicide();
	}
}

bool AVehiclePlayerController::ServerSuicide_Validate()
{
	return true;
}

void AVehiclePlayerController::ServerSuicide_Implementation()
{
	AVehicleGameState* GameState = GetWorld()->GetGameState<AVehicleGameState>();
	if (((GameState != nullptr) && (GameState->IsRaceActive())) || (GetNetMode() == NM_Standalone))
	{
		ABmwPawn* MyPawn = Cast<ABmwPawn>(GetPawn());
	
		if (MyPawn)
		{
			MyPawn->Die();
		}
	}
	if (((GameState != nullptr) && (GameState->IsRaceActive())) || (GetNetMode() == NM_Standalone))
	{
		ACoupePawn* MyPawn2 = Cast<ACoupePawn>(GetPawn());
		if (MyPawn2)
		{
			MyPawn2->Die();
		}
	}
}

