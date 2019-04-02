// Fill out your copyright notice in the Description page of Project Settings.

#include "StructurePrimitive.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AStructurePrimitive::AStructurePrimitive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision;

	StructureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Structure Mesh"));
	StructureMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AStructurePrimitive::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStructurePrimitive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

