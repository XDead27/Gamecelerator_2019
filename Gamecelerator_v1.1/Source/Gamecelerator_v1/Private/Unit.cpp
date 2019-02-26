// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Unit.h"
#include "Public/UnitAIController.h"
#include "Public/Structure.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isSelected = false;

	TargetPosition = GetActorLocation();

	AIControllerClass = AUnitAIController::StaticClass(); 
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
	ControllingAI = GetController();
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnit::setIsSelected(bool a)
{
	this->isSelected = a;
}

bool AUnit::getIsSelected()
{
	return isSelected;
}

AController * AUnit::getControllingAI()
{
	return ControllingAI;
}

EStatusToPlayer AUnit::getStatusToPlayer()
{
	return AttackVariables.status;
}

//Delegates attack to the AIController
void AUnit::SetActorToAttack(AActor * ActorToAttack)
{
	this->ActorToAttack = ActorToAttack;
}

AActor * AUnit::GetActorToAttack()
{
	return ActorToAttack;
}

float AUnit::GetDamagePerHit()
{
	return AttackVariables.DamagePerHit;
}

float AUnit::GetTimeBetweenHits()
{
	return AttackVariables.TimeBetweenHits;
}

float AUnit::GetAttackRange()
{
	return AttackVariables.AttackRange;
}

float AUnit::GetHealth()
{
	return HealthVariables.Health;
}

float AUnit::SetHealth(float Amount)
{
	HealthVariables.Health = Amount;
	return HealthVariables.Health;
}

float AUnit::GetMaxHealth()
{
	return HealthVariables.HealthMax;
}



