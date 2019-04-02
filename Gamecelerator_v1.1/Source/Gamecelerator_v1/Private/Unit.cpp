// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Unit.h"
#include "Public/UnitAIController.h"
#include "Public/Structure.h"
#include "Blueprint/UserWidget.h"
#include "Public/PlayerSpectatorPawnController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isSelected = false;

	TargetPosition = GetActorLocation();

	AIControllerClass = AUnitAIController::StaticClass(); 
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
	ControllingAI = GetController();
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HealthVariables.Health <= 0) {
		OnDeath();
		bIsDead = true;
	}

}

void AUnit::setIsSelected(bool a)
{
	this->isSelected = a;
}

bool AUnit::getIsSelected()
{
	return isSelected;
}

AController * AUnit::getControllingAI()
{
	return ControllingAI;
}

EStatusToPlayer AUnit::GetStatusToPlayer()
{
	return AttackVariables.status;
}

void AUnit::SetStatusToPlayer(EStatusToPlayer NewStatus)
{
	AttackVariables.status = NewStatus;
}


AActor * AUnit::GetActorToAttack()
{
	return ActorToAttack;
}

float AUnit::GetDamagePerHit()
{
	return AttackVariables.DamagePerHit;
}

float AUnit::GetTimeBetweenHits()
{
	return AttackVariables.TimeBetweenHits;
}

float AUnit::GetAttackRange()
{
	return AttackVariables.AttackRange;
}

float AUnit::GetHealth()
{
	return HealthVariables.Health;
}

float AUnit::SetHealth(float Amount)
{
	HealthVariables.Health = Amount;
	return HealthVariables.Health;
}

float AUnit::GetMaxHealth()
{
	return HealthVariables.HealthMax;
}

void AUnit::SetParsedActor(AActor * Actor)
{
	ParsedActor = Actor;
}

void AUnit::WaitForParsing(AActor* &a)
{
	if (a == nullptr) {
		APlayerSpectatorPawnController* playercont = Cast<APlayerSpectatorPawnController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		playercont->SetParsingSelectToUnit(this);

		if (ParsedActor) {
			a = ParsedActor;
			ParsedActor = nullptr;
		}
	}
}

void AUnit::WaitForParsing(TArray<AActor*> &arr)
{
	//tries every actor in the array
	for (AActor* e : arr) {
		if (!e) {
			APlayerSpectatorPawnController* playercont = Cast<APlayerSpectatorPawnController>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			playercont->SetParsingSelectToUnit(this);

			if (ParsedActor) {
				e = ParsedActor;
				ParsedActor = nullptr;
			}
			else {
				break;
			}
		}
	}
}

void AUnit::Ability_1()
{
}

void AUnit::Move(FVector NewLoc)
{
	TargetPosition = NewLoc;
	Attack(nullptr);
}

//Delegates attack to the AIController
void AUnit::Attack(AActor * ActorToAttack)
{
	this->ActorToAttack = ActorToAttack;
}

void AUnit::OnDeath()
{
	//Destroys the actor
	//Anything that is to be done before or after this action should be included in the
	//overriden function
	Destroy();
}

void AUnit::OnStop()
{
	Move(this->GetActorLocation());
	Attack(nullptr);
}



