// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/WorkerUnit.h"

AWorkerUnit::AWorkerUnit() {

	//specific setup
	HealthVariables.HealthMax = 50;
	HealthVariables.Health = HealthVariables.HealthMax;
	AttackVariables.DamagePerHit = 5;
	AttackVariables.TimeBetweenHits = 0.7;
	AttackVariables.AttackRange = 200;


}