// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/WorkerUnit.h"

AWorkerUnit::AWorkerUnit() {

	//specific setup
	HealthMax = 50;
	Health = HealthMax;
	DamagePerHit = 5;
	TimeBetweenHits = 0.7;
	AttackRange = 20;


}