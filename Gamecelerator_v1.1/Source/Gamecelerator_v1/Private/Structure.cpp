// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Structure.h"
#include "Public/Unit.h"
#include "Engine/World.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AStructure::AStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StructureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Structure Mesh"));
	StructureMesh->SetupAttachment(RootComponent);

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
	spawnedunit->SetStatusToPlayer(status);
}

bool AStructure::trainUnit()
{
	return false;
}

void AStructure::showInterface()
{
}

