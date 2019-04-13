// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Enumuri.h"
#include "RaceControllerInterface.h"
#include "PlayerSpectatorPawnController.generated.h"

class AUnit;
class UDiplomacyHandlerComponent;

/**
 * 
 */
UCLASS()
class GAMECELERATOR_V1_API APlayerSpectatorPawnController : public APlayerController, public IRaceControllerInterface
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
	int Resource1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EResourceType Resource1Type = EResourceType::RT_Wood;

public:
	///Native
	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	///Diplomacy
	//The component holding the array of allied, hostile and neutral controllers
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Diplomacy)
	class UDiplomacyHandlerComponent* DiplomacyComponent;
	UFUNCTION(BlueprintPure)
	bool VerifyCanControlActor();

	///Click Flags
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
	void UnitStop();

	///Abilities
	void ActorAbility1();
	void ActorAbility2();
	void ActorAbility3();
	void ActorAbility4();

	///Resource
	void AddResource(EResourceType restype, int amount);

	//Camera movements
	void MoveForward(float speed);
	void MoveRight(float speed);

	//Flag properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flags)
	ENextClickFlag DefaultFlag = ENextClickFlag::NCF_Select;

private:
	FVector2D CameraMovementInput;


};
