// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameceleratorModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMECELERATOR_V1_API AGameceleratorModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	TArray<TArray<AController*>> ListOfTeams;
};
