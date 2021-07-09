// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "VehiclePlayerController.generated.h"

class AVehicleTrackPoint;

UCLASS()
class AVehiclePlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadWrite, transient, Category=Game)
	AVehicleTrackPoint* LastTrackPoint;
	
	virtual void UnFreeze() override;

	void OnTrackPointReached(AVehicleTrackPoint* TrackPoint);

	void OnToggleInGameMenu();

	bool IsHandbrakeForced() const;
	
	void SetHandbrakeForced(bool bNewForced);

	void Suicide();

	UFUNCTION(reliable, server, WithValidation)
	void ServerSuicide();

protected:

	UPROPERTY(transient, replicated)
	bool bHandbrakeOverride;

	virtual void SetupInputComponent() override;
	virtual float GetMinRespawnDelay() override;
};
