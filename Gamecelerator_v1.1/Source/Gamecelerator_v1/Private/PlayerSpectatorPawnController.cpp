// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PlayerSpectatorPawnController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Public/Unit.h"
#include "Engine/World.h"
#include "Math/UnrealMathVectorCommon.h"
#include "ClickingComponent.h"


APlayerSpectatorPawnController::APlayerSpectatorPawnController() {
	bShowMouseCursor = true;

	ClickComp = CreateDefaultSubobject<UClickingComponent>(TEXT("ClickingComponent"));
}

void APlayerSpectatorPawnController::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerSpectatorPawnController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CameraMovementInput = CameraMovementInput.GetSafeNormal() * 1000.0f;
	FVector CameraLocation = GetPawn()->GetActorLocation();
	CameraLocation += GetPawn()->GetActorForwardVector() * CameraMovementInput.X * DeltaTime;
	CameraLocation += GetPawn()->GetActorRightVector() * CameraMovementInput.Y * DeltaTime;
	GetPawn()->SetActorLocation(CameraLocation);

	if (bMoveToMouseCursor)
	{
		GetUnderMouseCursor();
	}
}

void APlayerSpectatorPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &APlayerSpectatorPawnController::OnClickPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &APlayerSpectatorPawnController::OnClickReleased);

	InputComponent->BindAxis("MoveForward", this, &APlayerSpectatorPawnController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerSpectatorPawnController::MoveRight);

}

void APlayerSpectatorPawnController::GetUnderMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (ClickedActor)
	{
		if (AUnit* Temp = Cast<AUnit>(ClickedActor)) {
			if (ControlledUnit) {
				//If we click on an enemy with a unit already selected then make that unit attack the enemy
				if (ControlledUnit->GetStatusToPlayer() == EStatusToPlayer::STP_Friendly && (Temp->GetStatusToPlayer() == EStatusToPlayer::STP_Hostile || Temp->GetStatusToPlayer() == EStatusToPlayer::STP_Neutral)) {
					ControlledUnit->SetActorToAttack(Temp);
				}
				//Else just posses the new unit
				else {
					ControlledUnit->setIsSelected(false);
					ControlledUnit = Temp;
					ControlledUnit->setIsSelected(true);
				}
			}
			//If a unit is not already possesed then just posses the selected unit
			else {
				ControlledUnit = Temp;
				ControlledUnit->setIsSelected(true);
			}
		}
		else{
			if (ControlledUnit) {
				ControlledUnit->TargetPosition = Hit.ImpactPoint;
				ControlledUnit->SetActorToAttack(nullptr); //in cazul in care trebuia sa atace un actor, il deselecteaza
			}
		}
	}
	
}

void APlayerSpectatorPawnController::MoveForward(float speed) {
	CameraMovementInput.X = speed;
}

void APlayerSpectatorPawnController::MoveRight(float speed) {
	CameraMovementInput.Y = speed;
}

void APlayerSpectatorPawnController::OnClickPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
	ClickComp->Click();
}

void APlayerSpectatorPawnController::OnClickReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
	ClickComp->UnClick();
}