// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Structure.h"
#include "Public/Unit.h"
#include "Engine/World.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DiplomacyHandlerComponent.h"
#include "Kismet/GameplayStatics.h"

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
	
	//Pass the data to the interface because an interface cannot have blueprint variables
	//and neither does it have a reference to the world it's placed in
	PossesorIndex = ControllerIndex;
	SelfReference = this;

	Possesor = WaitForPossesor();

	if (Possesor)
		UE_LOG(LogTemp, Warning, TEXT("%s Possesor %s"), *this->GetName(), *Possesor->GetName())

}

// Called every frame
void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Possesor = WaitForPossesor();

	

}

// Spawns desired unit at some specified offset from the center location of the actor
void AStructure::SpawnUnit(TSubclassOf<AUnit> unitclass, EStatusToPlayer status)
{
	FVector spawnloc = GetActorLocation() + SpawningOffset;

	AUnit* spawnedunit = Cast<AUnit>(GetWorld()->SpawnActor(unitclass, &spawnloc));
	if (spawnedunit) {
		spawnedunit->PossesorIndex = this->PossesorIndex;
		spawnedunit->Possesor = this->Possesor;
	}
}

bool AStructure::TrainUnit()
{
	return false;
}

void AStructure::ShowInterface()
{
}

