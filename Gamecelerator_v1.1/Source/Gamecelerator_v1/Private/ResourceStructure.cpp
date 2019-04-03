// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceStructure.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

AResourceStructure::AResourceStructure() {
	ResourcesLeft = ResourcesMax;
}

void AResourceStructure::BeginPlay()
{
	Super::BeginPlay();

	ResourcesLeft = ResourcesMax;
}

int AResourceStructure::GetHarvested(int Amount)
{
	if (ResourcesLeft >= Amount) {
		ResourcesLeft -= Amount;
	}
	else {
		Amount = ResourcesLeft;
		ResourcesLeft = 0;
	}

	return Amount;
}
