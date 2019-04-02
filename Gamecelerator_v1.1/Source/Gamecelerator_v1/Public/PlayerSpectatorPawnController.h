// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Enumuri.h"
#include "PlayerSpectatorPawnController.generated.h"

class AUnit;
class UClickingComponent;

/**
 * 
 */
UCLASS()
class GAMECELERATOR_V1_API APlayerSpectatorPawnController : public APlayerController
{
	GENERATED_BODY()

	APlayerSpectatorPawnController();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AUnit* ControlledUnit;

	bool bIsClicking;
	bool bIsSelectObjectRequested;

	void OnClickPressed();
	void OnClickReleased();
	ENextClickFlag ClickFlag;

	//RESOURCES
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Resource1; //TODO

public:
	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	//Classifies clicks by attributed flags
	void ClassifyByFlag();
	//Attributes flags to clicks without specific input - will be modified by taste
	void GiveNormalFlags();

	//Selects an actor
	void SelectActor(AActor* ActorToSelect);
	void FlagAttack();
	void FlagSelect();
	void FlagMove();
	void FlagEsc();
	void FlagGather();

	void UnitAbility1();

	//Parsing of selected actors
	void SetParsingSelectToUnit(AUnit* UnitToParseTo);
	AUnit* UnitToParseTo;

	//Camera movements
	void MoveForward(float speed);
	void MoveRight(float speed);

	//Flag properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flags)
	ENextClickFlag DefaultFlag = ENextClickFlag::NCF_Select;

	//For clicking component ONLY
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Click)
	class UClickingComponent* ClickComp;
	AActor* ClickedActor;
	FVector ClickedLocation;

private:
	FVector2D CameraMovementInput;
};
