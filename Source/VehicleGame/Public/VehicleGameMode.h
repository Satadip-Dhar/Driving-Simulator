// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "VehicleGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRaceStartingDelegate);

class AVehicleGameState;
class AActor;

UCLASS()
class AVehicleGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category=Game)
	void StartRace();

	void FinishRace();

	/** Lock movement of newly logged in players if race is not active */
	void EnablePlayerLocking();

	// Begin AGameModeBase interface
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName = TEXT("")) override;
	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	virtual void Tick(float DeltaSeconds) override;

	bool IsRaceActive() const;

	bool HasRaceStarted() const;

	bool HasRaceFinished() const;

	UFUNCTION(BlueprintCallable, Category=Game)
	float GetRaceTimer() const;

	void SetGameInfoText(const FText& InText);

	const FText& GetGameInfoText() const;

	UFUNCTION(BlueprintCallable, Category=Game)
	void SetGamePaused(bool bIsPaused);

	UFUNCTION(BlueprintCallable, Category = Game)
	AVehicleGameState* GetVehicleGameState() const;

protected:

	FText GameInfoText;

	float RaceStartTime;

	float RaceFinishTime;

	/** Is player locking active? */
	bool bLockingActive;

	/** Lock all players until race starts */
	virtual void StartPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	void BroadcastRaceState();

	/** Delegate to broadcast about race starting */
	UPROPERTY(BlueprintAssignable)
	FRaceStartingDelegate OnRaceStarting;
};
