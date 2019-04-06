// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Structure.h"
#include "Public/Unit.h"
#include "Engine/World.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DiplomacyHandlerComponent.h"

// Sets default values
AStructure::AStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStructure::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Spawns desired unit at some specified offset from the center location of the actor
void AStructure::SpawnUnit(TSubclassOf<AUnit> unitclass, EStatusToPlayer status)
{
	FVector spawnloc = GetActorLocation() + SpawningOffset;

	AUnit* spawnedunit = Cast<AUnit>(GetWorld()->SpawnActor(unitclass, &spawnloc));
	if(spawnedunit)
		spawnedunit->Possesor = this->Possesor;
}

EStatusToPlayer AStructure::GetStatusToPlayer(AController* RequestingController)
{
	if (RequestingController == Possesor) {
		return EStatusToPlayer::STP_Owned;
	}

	UDiplomacyHandlerComponent* RequestingControllerDiplomacy = Cast<UDiplomacyHandlerComponent>(RequestingController->GetComponentByClass(UDiplomacyHandlerComponent::StaticClass()));

	if (RequestingControllerDiplomacy) {
		return *RequestingControllerDiplomacy->DiplomacyList.Find(Possesor);
	}
	else {
		return EStatusToPlayer::STP_None;
	}
}

bool AStructure::TrainUnit()
{
	return false;
}

void AStructure::ShowInterface()
{
}

