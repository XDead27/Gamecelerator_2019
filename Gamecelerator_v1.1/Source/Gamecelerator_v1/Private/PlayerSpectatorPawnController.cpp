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

	///See what is under the cursor for every frame
	//Declare the hit result
	FHitResult hitty;
	GetHitResultUnderCursor(ECC_Visibility, false, hitty);

	//Do not register the click unless the clicked actor is AUnit or AStructure
	if (Cast<AUnit>(hitty.GetActor()) || Cast<AStructurePrimitive>(hitty.GetActor()))
		ClickedActor = Cast<AActor>(hitty.GetActor());
	else
		ClickedActor = nullptr;
	//Always update the cursor location in world space
	ClickedLocation = hitty.ImpactPoint;
	
	if (bIsClicking) {
		//Attrivute normal flags depending on preference
		GiveNormalFlags();
		//Clasify actions by next click flags
		ClassifyByFlag();
		//**
		//Uncomment if you want single clicks
		//bIsClicking = false;
	}



	///DEBUG
	//if(ClickedActor)
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *ClickedActor->GetClass()->GetFName().ToString())

}

void APlayerSpectatorPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &APlayerSpectatorPawnController::OnClickPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &APlayerSpectatorPawnController::OnClickReleased);
	InputComponent->BindAction("Attack", IE_Pressed, this, &APlayerSpectatorPawnController::FlagAttack);
	InputComponent->BindAction("Move", IE_Pressed, this, &APlayerSpectatorPawnController::FlagMove);
	InputComponent->BindAction("Escape", IE_Pressed, this, &APlayerSpectatorPawnController::FlagEsc);
	InputComponent->BindAction("Stop", IE_Pressed, this, &APlayerSpectatorPawnController::UnitStop);

	InputComponent->BindAction("Ability1", IE_Pressed, this, &APlayerSpectatorPawnController::UnitAbility1);

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
			if (UnitToParseTo) {
				UnitToParseTo->SetParsedActor(ClickedActor);
				UnitToParseTo = nullptr;
			}
			else {
				SelectActor(ClickedActor);
			}
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
	if (ClickFlag == DefaultFlag) {
		//If a unit is selected but there is nothing under the cursor then activate the move flag
		if (ControlledUnit && !ClickedActor) {
			FlagMove();
		}
	}
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
	else if (ActorToSelect == nullptr) {
		if (ControlledUnit)
			ControlledUnit->setIsSelected(false);
		ControlledUnit = nullptr;
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

void APlayerSpectatorPawnController::FlagEsc()
{
	ClickFlag = ENextClickFlag::NCF_Esc;
}

void APlayerSpectatorPawnController::FlagGather()
{
	ClickFlag = ENextClickFlag::NCF_Gather;
}

void APlayerSpectatorPawnController::UnitStop()
{
	if(ControlledUnit)
		ControlledUnit->OnStop();
}

void APlayerSpectatorPawnController::UnitAbility1()
{
	if (ControlledUnit) {
		ControlledUnit->Ability_1();
	}
}

void APlayerSpectatorPawnController::AddResource(EResourceType restype, int amount)
{
	switch (restype)
	{
	case EResourceType::RT_Wood:
		Resource1 += amount;
		break;

	default:
		break;
	}
}

void APlayerSpectatorPawnController::SetParsingSelectToUnit(AUnit * UnitToParseTo)
{
	FlagSelect();
	this->UnitToParseTo = UnitToParseTo;
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
	ClickFlag = DefaultFlag;
	bIsClicking = false;
}