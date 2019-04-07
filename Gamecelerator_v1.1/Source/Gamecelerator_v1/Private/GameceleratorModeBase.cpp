// Fill out your copyright notice in the Description page of Project Settings.

#include "GameceleratorModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "DiplomacyHandlerComponent.h"
#include "RaceControllerPawn.h"


void AGameceleratorModeBase::BeginPlay() {
	Super::BeginPlay();

	for (int i = 0; i < AllControllers.Num(); i++) {
		for (const TPair<int, TSubclassOf<AController>> CurrController : AllControllers[i].Team) {
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			ARaceControllerPawn* CurrRacePawn = GetWorld()->SpawnActor<ARaceControllerPawn>(SpawnInfo);
			
			AController* CurrRaceController = GetWorld()->SpawnActor<AController>(CurrController.Value, SpawnInfo);
			CurrRaceController->Possess(CurrRacePawn);
			UDiplomacyHandlerComponent* DiplomacyComponent = Cast<UDiplomacyHandlerComponent>(CurrRaceController->GetComponentByClass(UDiplomacyHandlerComponent::StaticClass()));
			if (DiplomacyComponent) {
				DiplomacyComponent->ParentControllerTeamIndex = i;
				DiplomacyComponent->ParentControllerIndex = CurrController.Key;
			}
		}
	}


	TArray<AActor*> Controllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AController::StaticClass(), Controllers);

	//Get the teams
	for (AActor* a : Controllers) {
		UActorComponent* TryDiplomacyComponent = a->GetComponentByClass(UDiplomacyHandlerComponent::StaticClass());
		//If the actor has a diplomacy component implemented
		if (TryDiplomacyComponent) {
			//Do the casts
			UDiplomacyHandlerComponent* DiplomacyComponent = Cast<UDiplomacyHandlerComponent>(TryDiplomacyComponent);
			AController* CurrentController = Cast<AController>(a);

			//If this is the first controller of a certain team add a new blank team
			if (!ListOfTeams.IsValidIndex(DiplomacyComponent->ParentControllerTeamIndex)) {
				ListOfTeams.Insert(TArray<AController*>(), DiplomacyComponent->ParentControllerTeamIndex);
			}

			//Add the controller to the specified team
			ListOfTeams[DiplomacyComponent->ParentControllerTeamIndex].Add(CurrentController);
		}
	}

	//Update every controller's list of allies, neutrals and enemies
	for (TArray<AController*> CurrTeam : ListOfTeams) {
		for (AController* CurrInstance : CurrTeam) {
			UDiplomacyHandlerComponent* CurrInstanceDiplomacy = Cast<UDiplomacyHandlerComponent>(CurrInstance->GetComponentByClass(UDiplomacyHandlerComponent::StaticClass()));

			for (TArray<AController*> CurrChoosingTeam : ListOfTeams) {
				for (AController* CurrChoosingInstance : CurrChoosingTeam) {
					if(ListOfTeams.IndexOfByKey(CurrTeam) == ListOfTeams.IndexOfByKey(CurrChoosingTeam) && &CurrInstance != &CurrChoosingInstance)
						CurrInstanceDiplomacy->DiplomacyList.Add(CurrChoosingInstance, EStatusToPlayer::STP_Friendly);
					else if(ListOfTeams.IndexOfByKey(CurrChoosingTeam) == 0)
						CurrInstanceDiplomacy->DiplomacyList.Add(CurrChoosingInstance, EStatusToPlayer::STP_Neutral);
					else
						CurrInstanceDiplomacy->DiplomacyList.Add(CurrChoosingInstance, EStatusToPlayer::STP_Hostile);
				}
			}
		}
	}
}