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
		if (PossesedUnit->getIsSelected()) {
			eventClickedUnit();

			switch (PossesedUnit->getStatusToPlayer())
			{
			case EStatusToPlayer::STP_Friendly:
				if (PossesedUnit->GetActorToAttack()){
					Attack(Cast<AUnit>(PossesedUnit->GetActorToAttack()));
				}
				else {
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, PossesedUnit->TargetPosition);
				}

				break;

			case EStatusToPlayer::STP_Neutral:
				break;

			case EStatusToPlayer::STP_Hostile:
				break;

			default:
				break;
			}

		}
		else {
			//if we want to move or to do womething while we are not selecting it
			//code should go here
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

void AUnitAIController::Attack(AUnit * UnitToAttack)
{
	if (UnitToAttack) {
		if (FVector::Dist(PossesedUnit->GetActorLocation(),UnitToAttack->GetActorLocation()) > PossesedUnit->GetAttackRange()) {
			UAIBlueprintHelperLibrary::SimpleMoveToActor(this, UnitToAttack);

			UE_LOG(LogTemp, Warning, TEXT("Should go"))
		}
		else {
			//stop the unit and shoot
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, PossesedUnit->GetActorLocation());
			
			//timer so that the unit can only attack once every x seconds
			if (bCanAttack) {
				bCanAttack = false;
				UnitToAttack->GetDamaged(PossesedUnit->GetDamagePerHit());

				GetWorld()->GetTimerManager().SetTimer(UnitAttackHandle, this, &AUnitAIController::ResetAttack, PossesedUnit->GetTimeBetweenHits(), false);
			}
		}
	}
}

void AUnitAIController::Attack(AStructure * StructureToAttack)
{
}
