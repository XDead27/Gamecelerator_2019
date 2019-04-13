// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PlayerSpectatorPawnController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Public/Unit.h"
#include "Engine/World.h"
#include "Math/UnrealMathVectorCommon.h"
#include "ClickingComponent.h"
#include "DiplomacyHandlerComponent.h"
#include "RacePrimitive.h"


APlayerSpectatorPawnController::APlayerSpectatorPawnController() {
	bShowMouseCursor = true;

	//Subobjects
	DiplomacyComponent = CreateDefaultSubobject<UDiplomacyHandlerComponent>(TEXT("Diplomacy Component"));
	DiplomacyComponent->ParentControllerTeamIndex = 0;
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

	//Do not register the click unless the clicked actor is a IRacePrimitive actor
	if (Cast<IRacePrimitive>(hitty.GetActor()) && bIsClicking)
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
	if(auto Temp = Cast<IRacePrimitive>(ClickedActor))
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ClickedActor->GetName())

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

	InputComponent->BindAction("Ability1", IE_Pressed, this, &APlayerSpectatorPawnController::ActorAbility1);

	InputComponent->BindAxis("MoveForward", this, &APlayerSpectatorPawnController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerSpectatorPawnController::MoveRight);

}

bool APlayerSpectatorPawnController::VerifyCanControlActor()
{
	auto RaceActor = Cast<IRaceObjectInterface>(ControlledActor);

	if (RaceActor->GetStatusToPlayer(this) == EStatusToPlayer::STP_Owned)
		return true;
	else
		return false;
}

void APlayerSpectatorPawnController::ClassifyByFlag()
{
	/*switch (ClickFlag)
	{
	case ENextClickFlag::NCF_Move:
		if (ControlledUnit && VerifyCanControlUnit())
			ControlledUnit->Move(ClickedLocation);
		break;

	case ENextClickFlag::NCF_Attack:
		if (ControlledUnit && ClickedActor && VerifyCanControlUnit())
			ControlledUnit->Attack(ClickedActor);
		break;

	case ENextClickFlag::NCF_Select:
		if (ClickedActor) {
			if (UnitToParseTo) {
				UnitToParseTo->SetParameterActor(ClickedActor);
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
	}*/
}

void APlayerSpectatorPawnController::GiveNormalFlags()
{
	//if (ClickFlag == DefaultFlag) {
	//	//If a unit is selected but there is nothing under the cursor then activate the move flag
	//	if (ControlledUnit && !ClickedActor) {
	//		FlagMove();
	//	}
	//}
}

//To do with interfaces
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
	if(ControlledUnit && VerifyCanControlActor())
		ControlledUnit->OnStop();
}

void APlayerSpectatorPawnController::ActorAbility1()
{
	if (ControlledActor && VerifyCanControlActor()) {
		auto RaceActor = Cast<IRaceObjectInterface>(ControlledActor);
		if(RaceActor)
			RaceActor->Ability_1();
	}
}

void APlayerSpectatorPawnController::ActorAbility2()
{
	if (ControlledActor && VerifyCanControlActor()) {
		auto RaceActor = Cast<IRaceObjectInterface>(ControlledActor);
		if (RaceActor)
			RaceActor->Ability_2();
	}
}

void APlayerSpectatorPawnController::ActorAbility3()
{
	if (ControlledActor && VerifyCanControlActor()) {
		auto RaceActor = Cast<IRaceObjectInterface>(ControlledActor);
		if (RaceActor)
			RaceActor->Ability_3();
	}
}

void APlayerSpectatorPawnController::ActorAbility4()
{
	if (ControlledActor && VerifyCanControlActor()) {
		auto RaceActor = Cast<IRaceObjectInterface>(ControlledActor);
		if (RaceActor)
			RaceActor->Ability_4();
	}
}

void APlayerSpectatorPawnController::AddResource(EResourceType restype, int amount)
{
	if (restype == Resource1Type) {
		Resource1 += amount;
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
	//ClickComp->Click();

	bIsClicking = true;
}

void APlayerSpectatorPawnController::OnClickReleased()
{
	ClickFlag = DefaultFlag;
	bIsClicking = false;
}
