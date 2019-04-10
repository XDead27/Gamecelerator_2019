// Fill out your copyright notice in the Description page of Project Settings.

#include "RaceObjectInterface.h"
#include "DiplomacyHandlerComponent.h"
#include "PlayerSpectatorPawnController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )

// Add default functionality here for any IRaceObjectInterface functions that are not pure virtual.
EStatusToPlayer IRaceObjectInterface::GetStatusToPlayer(AController* RequestingController)
{
	if (RequestingController && Possesor) {
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
	else {
		UE_LOG(LogTemp, Warning, TEXT("Nu s-a gasit un posesor sau un controller care doreste conectarea"));

		if (!Possesor)
			UE_LOG(LogTemp, Warning, TEXT("Lipseste posesorul"))
		else if (!RequestingController)
			UE_LOG(LogTemp, Warning, TEXT("Lipseste requesting player"))


		return EStatusToPlayer::STP_None;
	}
	/*if(RequestingController)
		UE_LOG(LogTemp, Warning, TEXT("I am called for some fucking reason with argument %s"), *RequestingController->GetName())
	UE_LOG(LogTemp, Warning, TEXT("Ce pana mea"))*/

	//return EStatusToPlayer::STP_Friendly;
}


AController * IRaceObjectInterface::WaitForPossesor()
{
	if (!Possesor) {
		TArray<AActor*> ControllersArray;
		UGameplayStatics::GetAllActorsOfClass(SelfReference->GetWorld(), AController::StaticClass(), ControllersArray);

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

void IRaceObjectInterface::GetDamaged(float amount)
{
	IHealthRemaining -= amount;
}
