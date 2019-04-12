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

	bCanGather = true;
}


void AWorkerUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsGathering) {
		//UE_LOG(LogTemp, Warning, TEXT("Should Gather"))

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
	///If it is returning with resources
	if (bIsReturningFromResource) {
		//If it reached the destination
		if (this->IsOverlappingActor(StructureToGatherTo)) {
			//Stop movement
			StopMove();

			//Mark the next start to the Resource
			bIsReturningFromResource = false;

			//Add the resources to the Player
			APlayerSpectatorPawnController* playercont = Cast<APlayerSpectatorPawnController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if (playercont) {
				playercont->AddResource(HoldingResourcesType, HoldingResources);
				UE_LOG(LogTemp, Warning, TEXT("Added %d"), HoldingResources)
				HoldingResources = 0;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("PlayerConroller not found"))
			}
		}
		else {
			//Move until it reaches the minimum distance
			this->Move(StructureToGatherTo->GetActorLocation());
		}
	}
	///If it is going to harvest
	else {
		//If it reached the destination
		if(this->IsOverlappingActor(StructureToGatherFrom)){
			//Stop the movement
			StopMove();

			//Get the resource type of the material it's gathering
			HoldingResourcesType = StructureToGatherFrom->ResourceType;

			//If the Resource is not empty and the unit can still carry more items
			if (HoldingResources < MaxHoldResources && StructureToGatherFrom->GetResourcesLeft() > 0) {
				//Check for the gather timer (a unit can only cather a resource one every [GatherDelay] seconds)
				if (bCanGather) {
					//Start the timer again
					bCanGather = false;
					GetWorld()->GetTimerManager().SetTimer(UnitGatherHandle, this, &AWorkerUnit::ResetGather, GatherDelay, false);

					//Harvest the resources
					HoldingResources += StructureToGatherFrom->GetHarvested(MaxHarvestResources);
				}
			}
			//Else return with the resources
			else {
				bIsReturningFromResource = true;
			}
		}
		else{
			//Move until it reaches the minimum distance
			this->Move(StructureToGatherFrom->GetActorLocation());
		}
	}
}

void AWorkerUnit::StopGather()
{
	bIsGathering = false;
	StructureToGatherFrom = nullptr;
	StructureToGatherTo = nullptr;
}

void AWorkerUnit::ResetGather()
{
	bCanGather = true;
	GetWorld()->GetTimerManager().ClearTimer(UnitGatherHandle);
}

