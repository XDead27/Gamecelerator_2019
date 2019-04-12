// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Public/Enumuri.h"
#include "RaceObjectInterface.h"
#include "RacePrimitive.h"
#include "Unit.generated.h"

///*********************
//STRUCTS WITH VARIABLES
///*********************
USTRUCT(BlueprintType)
struct FHealthVariables
{
	GENERATED_USTRUCT_BODY()

	//Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float HealthMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health;
};

USTRUCT(BlueprintType)
struct FAttackVariables
{
	GENERATED_USTRUCT_BODY()

	//Relationship between player and unit
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	EStatusToPlayer status;

	UPROPERTY(VisibleAnywhere, Category = Damage)
	float DamagePerHit;

	UPROPERTY(VisibleAnywhere, Category = Damage)
	float TimeBetweenHits;

	UPROPERTY(VisibleAnywhere, Category = Damage)
	float AttackRange;

};

USTRUCT(BlueprintType)
struct FMovementVariables
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Movement)
	float WalkingSpeed;
};




///*********************
//CLASS
///*********************
UCLASS()
class GAMECELERATOR_V1_API AUnit : public ACharacter, public IRaceObjectInterface, public IRacePrimitive
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///Unit Functions
	virtual void Move(FVector NewLoc);
	virtual void StopMove();
	virtual void Attack(AActor* ActorToAttack);

	//Getters and Setters 
	void setIsSelected(bool);
	bool getIsSelected();
	AController* getControllingAI();

	///Status to Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Diplomacy)
	int ControllerIndex = 0;


	AActor* GetActorToAttack();

	UFUNCTION(BlueprintPure, Category = Variables)
	float GetDamagePerHit();

	UFUNCTION(BlueprintPure, Category = Variables)
	float GetTimeBetweenHits();

	UFUNCTION(BlueprintPure, Category = Variables)
	float GetAttackRange();

	UFUNCTION(BlueprintPure, Category = Variables)
	float GetHealth();
	UFUNCTION(BlueprintCallable, Category = Variables)
	float SetHealth(float Amount);

	UFUNCTION(BlueprintPure, Category = Variables)
	float GetMaxHealth();



	FVector TargetPosition;

protected:
	AController* ControllingAI;
	//ActorToAttack should be replaced with ParameterActor for future updates
	AActor* ActorToAttack;
	AActor* ParameterActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isSelected;

	//setup variables such as health, damage, etc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UnitSetup)
	FHealthVariables HealthVariables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UnitSetup)
	FAttackVariables AttackVariables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UnitSetup)
	FMovementVariables MovementVariables;

public:
	///Parameter Actors
	template <class T>
	void WaitForParsing(T* &a);
	void SetParameterActor(AActor* Actor);

	///Gameplay Functions
	//Ability abstract functions
	UFUNCTION(BlueprintCallable, Category = Abilities)
	virtual void Ability_1();

	//General natural functions
	virtual void OnDeath();
	virtual void OnStop();
};

//Template functions
template <class T>
void AUnit::WaitForParsing(T* &a) {
	if (a == nullptr) {
		APlayerSpectatorPawnController* playercont = Cast<APlayerSpectatorPawnController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (playercont)
			playercont->SetParsingSelectToUnit(this);
		else
			UE_LOG(LogTemp, Warning, TEXT("PlayerConroller not found"))


		if (Cast<T>(ParameterActor)) {
			a = Cast<T>(ParameterActor);
			ParameterActor = nullptr;
		}
	}
}
