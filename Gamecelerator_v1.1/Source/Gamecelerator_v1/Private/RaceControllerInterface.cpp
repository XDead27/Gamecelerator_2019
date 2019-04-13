// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceControllerInterface.h"

// Add default functionality here for any IRaceControllerInterface functions that are not pure virtual.

AActor * IRaceControllerInterface::GetClickedActor() 
{
	return ClickedActor;
}

AActor * IRaceControllerInterface::GetControlledActor()
{
	return ControlledActor;
}

FVector IRaceControllerInterface::GetClickedLocation()
{
	return ClickedLocation;
}

void IRaceControllerInterface::StartParsing()
{
	bRequestParsing = true;
}
