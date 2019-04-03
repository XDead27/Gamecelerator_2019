// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit.h"
#include "WorkerUnit.generated.h"

class AResourceStructure;
class AStructure;

/**
 * 
 */
UCLASS()
class GAMECELERATOR_V1_API AWorkerUnit : public AUnit
{
	GENERATED_BODY()
public:
	AWorkerUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	///Abilities
	//Overwrite of abilities
	virtual void Ability_1() override;
	virtual void OnStop() override;

	//Name of the overwrite functions
	void Gather();
	void StopGather();

public:
	//Specific attributes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = TypeDefaults)
	float GatherDistance = 200.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TypeDefaults)
	int MaxHoldResources = 5;

private:
	//Targets for gather
	AResourceStructure* StructureToGatherFrom;
	AStructure* StructureToGatherTo;

	//Gather flags
	bool bIsGathering = false;
	bool bIsReturningFromResource = false;

	//Variables
	int HoldingResources = 0;
};
