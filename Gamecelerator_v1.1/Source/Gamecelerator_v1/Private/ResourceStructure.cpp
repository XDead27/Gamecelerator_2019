// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceStructure.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

AResourceStructure::AResourceStructure() {
	
}

void AResourceStructure::GetHarvested(int Amount)
{
	ResourcesLeft -= Amount;
}
