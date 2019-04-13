// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enumuri.h"
#include "Kismet/GameplayStatics.h"
#include "Engine//World.h"
#include "RaceObjectInterface.generated.h"

class AController;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class URaceObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMECELERATOR_V1_API IRaceObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	///Diplomacy
	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	virtual EStatusToPlayer GetStatusToPlayer(AController* RequestingController);
	virtual AController* WaitForPossesor();
	int PossesorIndex = 0;
	AController* Possesor;
	AActor* SelfReference;

	///Health
	float IHealthMax;
	//Blueprint mixed functions
	UFUNCTION(BlueprintCallable)
	virtual void GetDamaged(float amount);

	///Abilities & functions
	UFUNCTION(BlueprintCallable, Category = Abilities)
	virtual void Ability_1() = 0;
	UFUNCTION(BlueprintCallable, Category = Abilities)
	virtual void Ability_2() = 0;
	UFUNCTION(BlueprintCallable, Category = Abilities)
	virtual void Ability_3() = 0;
	UFUNCTION(BlueprintCallable, Category = Abilities)
	virtual void Ability_4() = 0;


	///Parsing
	//Actor
	template <class T>
	void WaitForParsing(T* &a);
	void SetParameterActor(AActor* ActorForParsing);

	//Location
	FVector GetParameterLocation();

protected:
	float IHealthRemaining;

private:
	AActor* ParameterActor;
};

//Template functions TODO
template <class T>
void IRaceObjectInterface::WaitForParsing(T* &a) {
	if (a == nullptr) {
		auto RaceController = Cast<IRaceControllerInterface>(Possesor);
		if(RaceController)
			ParameterActor = RaceController->GetClickedActor();

		if (Cast<T>(ParameterActor)) {
			a = Cast<T>(ParameterActor);
			ParameterActor = nullptr;
		}
	}
}
