// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RaceAIControllerPrimitive.generated.h"

class UDiplomacyHandlerComponent;

/**
 * 
 */
UCLASS()
class GAMECELERATOR_V1_API ARaceAIControllerPrimitive : public AAIController
{
	GENERATED_BODY()
	
public:
	ARaceAIControllerPrimitive();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Diplomacy)
	class UDiplomacyHandlerComponent* DiplomacyComponent;
};
