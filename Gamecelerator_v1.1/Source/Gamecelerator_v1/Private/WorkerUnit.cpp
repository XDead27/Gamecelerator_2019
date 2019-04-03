// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/WorkerUnit.h"
#include "Public/PlayerSpectatorPawnController.h"
#include "Engine/World.h"
#include "ResourceStructure.h"
#include "Structure.h"
#include "Public/TimerManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


AWorkerUnit::AWorkerUnit() {

	//specific setup
	HealthVariables.HealthMax = 50;
	HealthVariables.Health = HealthVariables.HealthMax;
	AttackVariables.DamagePerHit = 5;
	AttackVariables.TimeBetweenHits = 0.7;
	AttackVariables.AttackRange = 200;

	GatherDistance = 100;

}

void AWorkerUnit::BeginPlay()
{
	Super::BeginPlay();
}


void AWorkerUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsGathering) {

		if (!(StructureToGatherFrom && StructureToGatherTo)) {
			WaitForParsing(StructureToGatherFrom);
			WaitForParsing(StructureToGatherTo);
		}
		else {
			Gather();
		}
	}
}

void AWorkerUnit::Ability_1()
{
	bIsGathering = true;
}

void AWorkerUnit::OnStop()
{
	AUnit::OnStop();
	StopGather();
}

void AWorkerUnit::Gather()
{
	if (bIsReturningFromResource) {
		this->Move(StructureToGatherTo->GetActorLocation());
		
		if (this->IsOverlappingActor(StructureToGatherTo)) {
			bIsReturningFromResource = false;

			APlayerSpectatorPawnController* playercont = Cast<APlayerSpectatorPawnController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if (playercont) {
				playercont->AddResource(EResourceType::RT_Wood, HoldingResources);
				UE_LOG(LogTemp, Warning, TEXT("Added %d"), HoldingResources)
				HoldingResources = 0;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("PlayerConroller not found"))
			}
		}
	}
	else {
		this->Move(StructureToGatherFrom->GetActorLocation());

		if(this->IsOverlappingActor(StructureToGatherFrom)){
			bIsReturningFromResource = true;

			if(HoldingResources <= MaxHoldResources)
				HoldingResources += StructureToGatherFrom->GetHarvested(5);
		}
	}
}

void AWorkerUnit::StopGather()
{
	bIsGathering = false;
	StructureToGatherFrom = nullptr;
	StructureToGatherTo = nullptr;
}

