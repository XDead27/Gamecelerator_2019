// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameceleratorModeBase.generated.h"

class AController;

USTRUCT(BlueprintType)
struct FNestedContainer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, TSubclassOf<AController>> Team;
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FNestedContainer> AllControllers;
};
