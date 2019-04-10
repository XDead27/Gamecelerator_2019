// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIController.generated.h"

class AUnit;
class AStructure;

/**
 * 
 */
UCLASS()
class GAMECELERATOR_V1_API AUnitAIController : public AAIController
{
	GENERATED_BODY()

	AUnitAIController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	AUnit* PossesedUnit;

protected:
	//For attack delay
	void ResetAttack();
	bool bCanAttack;
	FTimerHandle UnitAttackHandle;

public:
	void eventClickedUnit();

	//movement
	void moveCharacter();

	//attack
	void Attack(AActor* UnitToAttack);
};
