// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/UnitAIController.h"
#include "Public/Unit.h"
#include "Public/Structure.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Math/Vector.h"
#include "Public/TimerManager.h"

AUnitAIController::AUnitAIController() {
	PrimaryActorTick.bCanEverTick = true;
}

void AUnitAIController::BeginPlay() {
	Super::BeginPlay();

	PossesedUnit = Cast<AUnit>(GetPawn());

	if (PossesedUnit) {
		PossesedUnit->TargetPosition = PossesedUnit->GetActorLocation();
	}

	bCanAttack = true;
}

void AUnitAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PossesedUnit) {
		if (PossesedUnit->getIsSelected())
			eventClickedUnit();

		if (PossesedUnit->GetActorToAttack() && PossesedUnit->GetActorToAttack()->GetClass()->ImplementsInterface(URaceObjectInterface::StaticClass())){
			Attack(PossesedUnit->GetActorToAttack());
		}
		else {
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, PossesedUnit->TargetPosition);
		}

	}
	else {
		PossesedUnit = Cast<AUnit>(GetPawn());
	}
}

void AUnitAIController::ResetAttack()
{
	bCanAttack = true;
	GetWorld()->GetTimerManager().ClearTimer(UnitAttackHandle);
}

void AUnitAIController::eventClickedUnit()
{
	//TODO
}

void AUnitAIController::moveCharacter()
{
	
}

void AUnitAIController::Attack(AActor * ActorToAttack)
{
	if (ActorToAttack) {
		if (FVector::Dist(PossesedUnit->GetActorLocation(), ActorToAttack->GetActorLocation()) > PossesedUnit->GetAttackRange()) {
			UAIBlueprintHelperLibrary::SimpleMoveToActor(this, ActorToAttack);
		}
		else {
			//stop the unit and shoot
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, PossesedUnit->GetActorLocation());
			
			//timer so that the unit can only attack once every x seconds
			if (bCanAttack) {
				bCanAttack = false;
				//if(ActorToAttack->GetClass()->ImplementsInterface(URaceObjectInterface::StaticClass()))
				//	IRaceObjectInterface::Execute_GetDamaged(PossesedUnit->GetDamagePerHit());
				if (IRaceObjectInterface* RaceInterface = Cast<IRaceObjectInterface>(ActorToAttack))
					RaceInterface->GetDamaged(PossesedUnit->GetDamagePerHit());

				GetWorld()->GetTimerManager().SetTimer(UnitAttackHandle, this, &AUnitAIController::ResetAttack, PossesedUnit->GetTimeBetweenHits(), false);
			}
		}
	}
}
