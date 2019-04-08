// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceAIControllerPrimitive.h"
#include "DiplomacyHandlerComponent.h"

ARaceAIControllerPrimitive::ARaceAIControllerPrimitive() {
	DiplomacyComponent = CreateDefaultSubobject<UDiplomacyHandlerComponent>(TEXT("Diplomacy Component"));
}

