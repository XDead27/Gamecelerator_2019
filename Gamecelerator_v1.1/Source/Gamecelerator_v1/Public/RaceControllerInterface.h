// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RaceControllerInterface.generated.h"



// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class URaceControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMECELERATOR_V1_API IRaceControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual AActor* GetClickedActor();
	virtual AActor* GetControlledActor();
	virtual FVector GetClickedLocation();
	virtual void StartParsing();

protected:
	AActor* ControlledActor;
	AActor* ClickedActor;
	FVector ClickedLocation;

	///Parsing
	bool bRequestParsing = false;
};
