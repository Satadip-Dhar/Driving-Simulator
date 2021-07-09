// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "VehicleGame.h"
#include "VehicleBlueprintLibrary.h"
#include "UI/VehicleHUD.h"
#include "VehicleGameMode.h"

UVehicleBlueprintLibrary::UVehicleBlueprintLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

AVehicleGameMode* GetGameFromContextObject(UObject* WorldContextObject)
{
	UWorld* const MyWorld = GEngine->GetWorldFromContextObject(WorldContextObject);
	check(MyWorld);

	AVehicleGameMode* const MyGame = MyWorld->GetAuthGameMode<AVehicleGameMode>();
	return MyGame;
}

void UVehicleBlueprintLibrary::FinishRace(UObject* WorldContextObject)
{
	AVehicleGameMode* const MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		MyGame->FinishRace();
	}
}

void UVehicleBlueprintLibrary::SetInfoText(UObject* WorldContextObject, FString InfoText)
{
	AVehicleGameMode* const MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		MyGame->SetGameInfoText(FText::FromString(InfoText));
	}
}

 void UVehicleBlueprintLibrary::HideInfoText(UObject* WorldContextObject)
 {
 	AVehicleGameMode* const MyGame = GetGameFromContextObject(WorldContextObject);
	if (MyGame)
	{
		MyGame->SetGameInfoText(FText::GetEmpty());
	}
 }

 void UVehicleBlueprintLibrary::ShowGameMenu(UObject* WorldContextObject)
 {
	 UWorld* const MyWorld = GEngine->GetWorldFromContextObject(WorldContextObject);
	 APlayerController* LocalPC = GEngine->GetFirstLocalPlayerController(MyWorld);
	 AVehicleHUD* MyHUD = LocalPC ? Cast<AVehicleHUD>(LocalPC->GetHUD()) : nullptr;
	 if (MyHUD)
	 {
		 if (!MyHUD->IsGameMenuUp())
		 {
			 MyHUD->ToggleGameMenu();
		 }
	 }
 }

 void UVehicleBlueprintLibrary::ShowHUD(UObject* WorldContextObject, bool bEnable)
 {
	 UWorld* const MyWorld = GEngine->GetWorldFromContextObject(WorldContextObject);
	 APlayerController* LocalPC = GEngine->GetFirstLocalPlayerController(MyWorld);
	 AVehicleHUD* MyHUD = LocalPC ? Cast<AVehicleHUD>(LocalPC->GetHUD()) : nullptr;
	 if (MyHUD)
	 {
		 MyHUD->EnableHUD(bEnable);
	 }
 }


