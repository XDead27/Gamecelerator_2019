// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Gamecelerator_v1GameMode.h"
#include "Gamecelerator_v1PlayerController.h"
#include "Gamecelerator_v1Character.h"
#include "UObject/ConstructorHelpers.h"

AGamecelerator_v1GameMode::AGamecelerator_v1GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGamecelerator_v1PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}