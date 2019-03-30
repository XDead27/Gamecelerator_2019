// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	bool bMoveToMouseCursor;
	bool bIsSelectObjectRequested;

	void OnClickPressed();
	void OnClickReleased();

	//RESOURCES
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Resource1; //TODO

public:
	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	//Must fix this
	void GetUnderMouseCursor();

	//Camera movements
	void MoveForward(float speed);
	void MoveRight(float speed);

	//For clicking component ONLY
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Click)
	class UClickingComponent* ClickComp;
	AActor* ClickedActor;

private:
	FVector2D CameraMovementInput;
};
