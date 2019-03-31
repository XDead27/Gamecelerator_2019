// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Unit.h"
#include "Structure.h"
#include "ClickingComponent.generated.h"

class APlayerSpectatorPawnController;

USTRUCT(BlueprintType)
struct FHitActorStats
{
	GENERATED_USTRUCT_BODY()
	//Actor hit
	AActor* HitActor;

	//AUnit or AStructure - null if it is not one of them
	TSubclassOf<AActor> ActorType;

	//Actor's location - or the location under the mouse cursor
	FVector ActorLocation;

	EStatusToPlayer ActorStatus;
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMECELERATOR_V1_API UClickingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UClickingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//The owner of this component
	APlayerSpectatorPawnController* Parent;

	//
	bool bNewSelection = false;
	
	bool bIsClicking = false;

	//A buffer which retains the last found actor
	AActor* ActorBuffer;

	//The type of actor to seach for
	TSubclassOf<class AActor> ActorToSearch;

	FHitResult RootActorUnderMousePos;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	///CLICK
	//Registers a click
	void Click();
	//Registers an unclick
	void UnClick();

	//Gets the actor of class T at the hit location
	template <class T>
	T* GetObjectAtHit(FHitResult Hit);	

	//Gets the actor of class T under the mouse cursor
	template <class T>
	T* GetObjectAtHitUnderMouseCursor();

	//Gets the actor of class AActor under the mouse cursor
	FHitActorStats GetObjectUnderMouseCursorAttributes();

	///SELECTION SEQUENCE
	//Starts a new selection sequence
	void NewSelection(TSubclassOf<AActor> ClassToSearch);
	void NewSelection(ENextClickFlag NextFlag);
	//Ends the new selection and returns the found actor
	AActor* EndSelection();
};
