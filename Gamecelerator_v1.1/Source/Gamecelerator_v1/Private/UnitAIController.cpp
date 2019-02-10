// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/UnitAIController.h"
#include "Public/Unit.h"
#include "Public/Structure.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AUnitAIController::AUnitAIController() {
	PrimaryActorTick.bCanEverTick = true;
}

void AUnitAIController::BeginPlay() {
	Super::BeginPlay();

	PossesedUnit = Cast<AUnit>(GetPawn());

	if (PossesedUnit) {
		PossesedUnit->TargetPosition = PossesedUnit->GetActorLocation();
	}
}

void AUnitAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!PossesedUnit)
		PossesedUnit = Cast<AUnit>(GetPawn());

	if (PossesedUnit) {
		if (PossesedUnit->getIsSelected()) {
			eventClickedUnit();

			switch (PossesedUnit->getStatusToPlayer())
			{
			case EStatusToPlayer::STP_Friendly:
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, PossesedUnit->TargetPosition);
				break;

			case EStatusToPlayer::STP_Neutral:
				break;

			case EStatusToPlayer::STP_Hostile:
				break;

			default:
				break;
			}

			if (PossesedUnit->GetActorToAttack()) {
				Attack(Cast<AUnit>(PossesedUnit->GetActorToAttack()));
				UE_LOG(LogTemp, Warning, TEXT("Should be attacking"))
			}
		}
	}
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
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, UnitToAttack->GetActorLocation());
		}
		else {
			//implement delay
			UnitToAttack->GetDamaged(PossesedUnit->GetDamagePerHit() / PossesedUnit->GetTimeBetweenHits() / GetWorld()->GetDeltaSeconds());
		}
	}
}

void AUnitAIController::Attack(AStructure * StructureToAttack)
{
}
