// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Unit.h"
#include "Public/UnitAIController.h"
#include "Public/Structure.h"
#include "Blueprint/UserWidget.h"
#include "Public/PlayerSpectatorPawnController.h"
#include "Kismet/GameplayStatics.h"
#include "DiplomacyHandlerComponent.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

// Sets default values
AUnit::AUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isSelected = false;


	AIControllerClass = AUnitAIController::StaticClass(); 
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
	//Pass the data to the interface because an interface cannot have blueprint variables
	//and neither does it have a reference to the world it's placed in
	PossesorIndex = ControllerIndex;
	SelfReference = this;
	IHealthMax = HealthVariables.HealthMax;
	IHealthRemaining = IHealthMax;

	ControllingAI = GetController();
	TargetPosition = GetActorLocation();
	Possesor = WaitForPossesor();

	if(Possesor)
		UE_LOG(LogTemp, Warning, TEXT("%s (%d:%d) Possesor %s"), *this->GetName(), ControllerIndex, PossesorIndex, *Possesor->GetName())
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Possesor = WaitForPossesor();

	/*if (Possesor)
		UE_LOG(LogTemp, Warning, TEXT("%s Possesor %s"), *this->GetName(), *Possesor->GetName())*/

	if (IHealthRemaining <= 0) {
		OnDeath();
	}

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
	return IHealthRemaining;
}

float AUnit::SetHealth(float Amount)
{
	IHealthRemaining = Amount;
	return IHealthRemaining;
}

float AUnit::GetMaxHealth()
{
	return HealthVariables.HealthMax;
}

void AUnit::SetParameterActor(AActor * Actor)
{
	ParameterActor = Actor;
}

void AUnit::Ability_1()
{
}

void AUnit::Move(FVector NewLoc)
{
	TargetPosition = NewLoc;
	Attack(nullptr);
}

void AUnit::StopMove()
{
	Move(this->GetActorLocation());
}

//Delegates attack to the AIController
void AUnit::Attack(AActor * ActorToAttack)
{
	this->ActorToAttack = ActorToAttack;
}

void AUnit::OnDeath()
{
	//Destroys the actor
	//Anything that is to be done before or after this action should be included in the
	//overriden function
	Destroy();
}

void AUnit::OnStop()
{
	Move(this->GetActorLocation());
	Attack(nullptr);
}



