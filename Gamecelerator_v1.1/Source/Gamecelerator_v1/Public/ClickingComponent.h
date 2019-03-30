// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClickingComponent.generated.h"

class APlayerSpectatorPawnController;

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

	//Registers a click
	void Click();
	//Registers an unclick
	void UnClick();

	//Gets the actor of class T
	template <class T>
	T* GetObjectAtHit(FHitResult Hit);	

	//Starts a new selection sequence
	void NewSelection(TSubclassOf<AActor> ClassToSearch);
	//Ends the new selection and returns the found actor
	AActor* EndSelection();
};
