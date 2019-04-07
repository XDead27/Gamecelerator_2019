// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Structure.h"
#include "Public/Unit.h"
#include "Engine/World.h"
#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DiplomacyHandlerComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStructure::AStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStructure::BeginPlay()
{
	Super::BeginPlay();
	
	Possesor = WaitForPossesor();

	if (Possesor)
		UE_LOG(LogTemp, Warning, TEXT("%s Possesor %s"), *this->GetName(), *Possesor->GetName())

}

// Called every frame
void AStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Possesor = WaitForPossesor();

	

}

AController * AStructure::WaitForPossesor()
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

	return nullptr;
}

// Spawns desired unit at some specified offset from the center location of the actor
void AStructure::SpawnUnit(TSubclassOf<AUnit> unitclass, EStatusToPlayer status)
{
	FVector spawnloc = GetActorLocation() + SpawningOffset;

	AUnit* spawnedunit = Cast<AUnit>(GetWorld()->SpawnActor(unitclass, &spawnloc));
	if (spawnedunit) {
		spawnedunit->PossesorIndex = this->PossesorIndex;
		spawnedunit->Possesor = this->Possesor;
	}
}

EStatusToPlayer AStructure::GetStatusToPlayer(AController* RequestingController)
{
	if (RequestingController == Possesor) {
		return EStatusToPlayer::STP_Owned;
	}

	UDiplomacyHandlerComponent* RequestingControllerDiplomacy = Cast<UDiplomacyHandlerComponent>(RequestingController->GetComponentByClass(UDiplomacyHandlerComponent::StaticClass()));

	if (RequestingControllerDiplomacy) {
		return RequestingControllerDiplomacy->DiplomacyList.FindRef(Possesor);
	}
	else {
		return EStatusToPlayer::STP_None;
	}
}

bool AStructure::TrainUnit()
{
	return false;
}

void AStructure::ShowInterface()
{
}

