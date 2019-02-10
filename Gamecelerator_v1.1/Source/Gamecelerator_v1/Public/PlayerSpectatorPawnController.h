// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerSpectatorPawnController.generated.h"

class AUnit;

/**
 * 
 */
UCLASS()
class GAMECELERATOR_V1_API APlayerSpectatorPawnController : public APlayerController
{
	GENERATED_BODY()

	APlayerSpectatorPawnController();

private:
	AUnit* ControlledUnit;

	bool bMoveToMouseCursor;

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
public:
	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	void GetUnderMouseCursor();
	void GetTouchedLocation(const FVector Location);

	//
	void MoveForward(float speed);
	void MoveRight(float speed);

private:
	FVector2D CameraMovementInput;
};
