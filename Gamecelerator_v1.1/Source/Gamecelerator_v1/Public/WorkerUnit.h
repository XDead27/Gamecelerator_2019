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

protected:
	//Virtual function
	virtual void WaitForParsing(AActor* &a) override;

public:
	//Specific attributes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TypeDefaults)
	float GatherDistance;

private:
	AResourceStructure* StructureToGatherFrom;
	AStructure* StructureToGatherTo;

	bool bIsGathering = false;
	bool bIsReturningFromResource = false;
};
