// Fill out your copyright notice in the Description page of Project Settings.

#include "GameceleratorModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "DiplomacyHandlerComponent.h"
#include "RaceControllerPawn.h"
#include "PlayerSpectatorPawnController.h"


void AGameceleratorModeBase::BeginPlay() {
	Super::BeginPlay();

	for (int i = 0; i < AllControllers.Num(); i++) {
		for (const TPair<int, TSubclassOf<AController>> CurrController : AllControllers[i].Team) {
			
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AController* CurrRaceController;
			ARaceControllerPawn* CurrRacePawn;

			if (!CurrController.Value->IsChildOf(APlayerController::StaticClass())) {
				CurrRacePawn = GetWorld()->SpawnActor<ARaceControllerPawn>(SpawnInfo);

				CurrRaceController = GetWorld()->SpawnActor<AController>(CurrController.Value, SpawnInfo);

				CurrRaceController->Possess(CurrRacePawn);
			}
			else {
				CurrRaceController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			}

			UDiplomacyHandlerComponent* DiplomacyComponent = Cast<UDiplomacyHandlerComponent>(CurrRaceController->GetComponentByClass(UDiplomacyHandlerComponent::StaticClass()));

			if (DiplomacyComponent) {
				DiplomacyComponent->ParentControllerTeamIndex = i;
				DiplomacyComponent->ParentControllerIndex = CurrController.Key;
			}
		}
	}


	TArray<AActor*> Controllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AController::StaticClass(), Controllers);

	for (AActor* a : Controllers) {
		if (UDiplomacyHandlerComponent* CompRef = Cast<UDiplomacyHandlerComponent>(a->GetComponentByClass(UDiplomacyHandlerComponent::StaticClass()))) {
			for (AActor* b : Controllers) {
				if (a != b) {
					if (UDiplomacyHandlerComponent* bCompRef = Cast<UDiplomacyHandlerComponent>(b->GetComponentByClass(UDiplomacyHandlerComponent::StaticClass()))) {
						if (bCompRef->ParentControllerTeamIndex == CompRef->ParentControllerTeamIndex) {
							CompRef->DiplomacyList.Add(Cast<AController>(b), EStatusToPlayer::STP_Friendly);
						}
						else if (bCompRef->ParentControllerTeamIndex == 0) {
							CompRef->DiplomacyList.Add(Cast<AController>(b), EStatusToPlayer::STP_Neutral);
						}
						else {
							CompRef->DiplomacyList.Add(Cast<AController>(b), EStatusToPlayer::STP_Hostile);
						}
					}
				}
			}
		}
	}
}