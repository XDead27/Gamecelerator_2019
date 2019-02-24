// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/WorkerUnit.h"

AWorkerUnit::AWorkerUnit() {

	//specific setup
	SetupVariables.HealthMax = 50;
	SetupVariables.Health = SetupVariables.HealthMax;
	SetupVariables.DamagePerHit = 5;
	SetupVariables.TimeBetweenHits = 0.7;
	SetupVariables.AttackRange = 200;


}