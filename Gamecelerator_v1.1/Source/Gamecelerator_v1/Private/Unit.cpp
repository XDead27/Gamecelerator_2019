// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Unit.h"
#include "Public/UnitAIController.h"
#include "Public/Structure.h"
#include "Blueprint/UserWidget.h"
#include "Public/PlayerSpectatorPawnController.h"
#include "Kismet/GameplayStatics.h"
#include "DiplomacyHandlerComponent.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

// Sets default values
AUnit::AUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isSelected = false;


	AIControllerClass = AUnitAIController::StaticClass(); 
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	
	ControllingAI = GetController();
	TargetPosition = GetActorLocation();
	Possesor = WaitForPossesor();

	if(Possesor)
		UE_LOG(LogTemp, Warning, TEXT("%s Possesor %s"), *this->GetName(), *Possesor->GetName())
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Possesor = WaitForPossesor();

	/*if (Possesor)
		UE_LOG(LogTemp, Warning, TEXT("%s Possesor %s"), *this->GetName(), *Possesor->GetName())*/

	if (HealthVariables.Health <= 0) {
		OnDeath();
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

EStatusToPlayer AUnit::GetStatusToPlayer(AController* RequestingController)
{
	if (RequestingController && Possesor) {
		if (RequestingController == Possesor) {
			return EStatusToPlayer::STP_Owned;
		}

		UDiplomacyHandlerComponent* RequestingControllerDiplomacy = Cast<UDiplomacyHandlerComponent>(Possesor->GetComponentByClass(UDiplomacyHandlerComponent::StaticClass()));

		if (RequestingControllerDiplomacy) {	
			return RequestingControllerDiplomacy->DiplomacyList.FindRef(RequestingController);
		}
		else {
			return EStatusToPlayer::STP_None;
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Nu s-a gasit un posesor sau un controller care doreste conectarea: %d"));

		if (!Possesor)
			UE_LOG(LogTemp, Warning, TEXT("Lipseste posesorul"))
		else if(!RequestingController)
			UE_LOG(LogTemp, Warning, TEXT("Lipseste requesting player"))


		return EStatusToPlayer::STP_None;
	}
	/*if(RequestingController)
		UE_LOG(LogTemp, Warning, TEXT("I am called for some fucking reason with argument %s"), *RequestingController->GetName())
	UE_LOG(LogTemp, Warning, TEXT("Ce pana mea"))*/

	//return EStatusToPlayer::STP_Friendly;
}

AController * AUnit::WaitForPossesor()
{
	if (!Possesor) {
		TArray<AActor*> ControllersArray;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AController::StaticClass(), ControllersArray);

		for (AActor* a : ControllersArray) {
			if (UDiplomacyHandlerComponent* DipRef = Cast<UDiplomacyHandlerComponent>(a->GetComponentByClass(UDiplomacyHandlerComponent::StaticClass()))) {
				if (DipRef->ParentControllerIndex == this->PossesorIndex) {
					return Cast<AController>(a);
				}
			}
		}
	}

	return Possesor;
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

void AUnit::SetParameterActor(AActor * Actor)
{
	ParameterActor = Actor;
}

void AUnit::Ability_1()
{
}

void AUnit::Move(FVector NewLoc)
{
	TargetPosition = NewLoc;
	Attack(nullptr);
}

void AUnit::StopMove()
{
	Move(this->GetActorLocation());
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



