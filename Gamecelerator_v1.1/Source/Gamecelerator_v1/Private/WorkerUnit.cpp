// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/WorkerUnit.h"
#include "Public/PlayerSpectatorPawnController.h"
#include "Engine/World.h"
#include "ResourceStructure.h"
#include "Structure.h"
#include "Public/TimerManager.h"
#include "Components/BoxComponent.h"

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
		UE_LOG(LogTemp, Warning, TEXT("macar a intrat aici"))

		if (!(StructureToGatherFrom && StructureToGatherTo)) {
			AActor* Temp = nullptr;
			WaitForParsing(Temp);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *StructureToGatherTo->GetName(), *StructureToGatherFrom->GetName())

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
	StopGather();
}

void AWorkerUnit::Gather()
{
	if (bIsReturningFromResource) {
		this->TargetPosition = StructureToGatherTo->GetActorLocation();
		
		if (FVector::Dist(this->GetActorLocation(), StructureToGatherTo->GetActorLocation()) < GatherDistance) {
			bIsReturningFromResource = false;
		}
	}
	else {
		this->TargetPosition = StructureToGatherFrom->GetActorLocation();

		UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), StructureToGatherFrom->GetComponentsBoundingBox().GetSize().X, StructureToGatherFrom->GetComponentsBoundingBox().GetSize().Y, StructureToGatherFrom->GetComponentsBoundingBox().GetSize().Z);

		if (FVector::Dist(this->GetActorLocation(), StructureToGatherFrom->GetActorLocation()) < GatherDistance) {
			bIsReturningFromResource = true;
		}
	}
}

void AWorkerUnit::StopGather()
{
	bIsGathering = false;
	StructureToGatherFrom = nullptr;
	StructureToGatherTo = nullptr;
}

void AWorkerUnit::WaitForParsing(AActor *& a)
{
	AUnit::WaitForParsing(a);

	/*if (a) {
		if (Cast<AResourceStructure>(a) && !StructureToGatherFrom) {
			StructureToGatherFrom = Cast<AResourceStructure>(a);
		}
		else {
			a = nullptr;
		}

		if (Cast<AStructure>(a) && !StructureToGatherTo) {
			StructureToGatherTo = Cast<AStructure>(a);
		}
		else {
			a = nullptr;
		}
	}*/
}
