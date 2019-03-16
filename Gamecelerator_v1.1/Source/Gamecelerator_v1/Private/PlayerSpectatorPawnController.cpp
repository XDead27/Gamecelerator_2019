// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PlayerSpectatorPawnController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Public/Unit.h"
#include "Engine/World.h"
#include "Math/UnrealMathVectorCommon.h"


APlayerSpectatorPawnController::APlayerSpectatorPawnController() {
	bShowMouseCursor = true;
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

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &APlayerSpectatorPawnController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &APlayerSpectatorPawnController::OnSetDestinationReleased);

	InputComponent->BindAxis("MoveForward", this, &APlayerSpectatorPawnController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerSpectatorPawnController::MoveRight);

}

void APlayerSpectatorPawnController::GetUnderMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		if (AUnit* Temp = Cast<AUnit>(Hit.Actor)) {
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

void APlayerSpectatorPawnController::GetTouchedLocation(const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		if (Cast<AUnit>(HitResult.Actor)) {
			UE_LOG(LogTemp, Warning, TEXT("E o unitate"))
		}
		else {
			// We hit something, move there
		}
	}
}

void APlayerSpectatorPawnController::MoveForward(float speed) {
	CameraMovementInput.X = speed;
}

void APlayerSpectatorPawnController::MoveRight(float speed) {
	CameraMovementInput.Y = speed;
}

void APlayerSpectatorPawnController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void APlayerSpectatorPawnController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}