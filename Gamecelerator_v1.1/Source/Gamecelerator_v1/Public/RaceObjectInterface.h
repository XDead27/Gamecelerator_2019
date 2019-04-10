// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enumuri.h"
#include "RaceObjectInterface.generated.h"

class AController;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class URaceObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMECELERATOR_V1_API IRaceObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	///Diplomacy
	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	virtual EStatusToPlayer GetStatusToPlayer(AController* RequestingController);
	virtual AController* WaitForPossesor();
	int PossesorIndex = 0;
	AController* Possesor;
	AActor* SelfReference;

	///Health
	float IHealthMax;
	//Blueprint mixed functions
	UFUNCTION(BlueprintCallable)
	virtual void GetDamaged(float amount);

protected:
	float IHealthRemaining;
};
