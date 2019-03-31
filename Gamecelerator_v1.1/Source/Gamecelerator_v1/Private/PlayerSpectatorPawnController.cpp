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

	
	FHitResult hitty;
	GetHitResultUnderCursor(ECC_Visibility, false, hitty);

	//Do not register the click unless the clicked actor is AUnit or AStructure
	if (Cast<AUnit>(hitty.GetActor()) || Cast<AStructure>(hitty.GetActor()))
		ClickedActor = Cast<AActor>(hitty.GetActor());
	ClickedLocation = hitty.ImpactPoint;
	
	if(bIsClicking)
		//Clasify actions by next click flags
		ClassifyByFlag();

}

void APlayerSpectatorPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &APlayerSpectatorPawnController::OnClickPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &APlayerSpectatorPawnController::OnClickReleased);
	InputComponent->BindAction("Attack", IE_Pressed, this, &APlayerSpectatorPawnController::FlagAttack);
	InputComponent->BindAction("Move", IE_Pressed, this, &APlayerSpectatorPawnController::FlagMove);

	InputComponent->BindAxis("MoveForward", this, &APlayerSpectatorPawnController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerSpectatorPawnController::MoveRight);

}

void APlayerSpectatorPawnController::ClassifyByFlag()
{
	switch (ClickFlag)
	{
	case ENextClickFlag::NCF_Move:
		if (ControlledUnit)
			ControlledUnit->Move(ClickedLocation);
		break;

	case ENextClickFlag::NCF_Attack:
		if (ControlledUnit && ClickedActor)
			ControlledUnit->Attack(ClickedActor);
		break;

	case ENextClickFlag::NCF_Select:
		if (ClickedActor) {
			SelectActor(ClickedActor);
		}
		break;

	case ENextClickFlag::NCF_Esc:
		SelectActor(nullptr);
		break;

	default:
		break;
	}
}

void APlayerSpectatorPawnController::GiveNormalFlags()
{
	//TODO
}

void APlayerSpectatorPawnController::SelectActor(AActor* ActorToSelect)
{
	if (Cast<AUnit>(ActorToSelect)) {
		if(ControlledUnit)
			ControlledUnit->setIsSelected(false);
		ControlledUnit = Cast<AUnit>(ActorToSelect);
		ControlledUnit->setIsSelected(true);
		ControlledUnit->Move(ControlledUnit->GetActorLocation());
	}
}

void APlayerSpectatorPawnController::FlagAttack()
{
	ClickFlag = ENextClickFlag::NCF_Attack;
}

void APlayerSpectatorPawnController::FlagSelect()
{
	ClickFlag = ENextClickFlag::NCF_Select;
}

void APlayerSpectatorPawnController::FlagMove()
{
	ClickFlag = ENextClickFlag::NCF_Move;
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
	//ClickComp->Click();

	bIsClicking = true;
}

void APlayerSpectatorPawnController::OnClickReleased()
{
	// clear flag to indicate we should stop updating the destination
	ClickFlag = ENextClickFlag::NCF_Select;
	//ClickComp->UnClick();

	bIsClicking = false;
}