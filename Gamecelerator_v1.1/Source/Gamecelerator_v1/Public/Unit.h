// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Public/Enumuri.h"
#include "Unit.generated.h"

///*********************
//ENUMS
///*********************
UENUM(BlueprintType)
enum class EStatusToPlayer : uint8
{
	STP_Friendly	UMETA(DisplayName = "Friendly"),
	STP_Neutral		UMETA(DisplayName = "Neutral"),
	STP_Hostile		UMETA(DisplayName = "Hostile")
};




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
class GAMECELERATOR_V1_API AUnit : public ACharacter
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

	//Getters and Setters 
	void setIsSelected(bool);
	bool getIsSelected();
	AController* getControllingAI();

	UFUNCTION(BlueprintPure, Category = Variables)
	EStatusToPlayer GetStatusToPlayer();
	UFUNCTION(BlueprintCallable, Category = Variables)
	void SetStatusToPlayer(EStatusToPlayer status);

	void SetActorToAttack(AActor* ActorToAttack);
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

	//Blueprint mixed functions
	UFUNCTION(BlueprintImplementableEvent)
	void GetDamaged(float amount);

	FVector TargetPosition;

protected:
	AController* ControllingAI;
	AActor* ActorToAttack;
	
	//nu cred ca ne trebuie momentan
	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isSelected;

	//setup variables such as health, damage, etc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UnitSetup)
	FHealthVariables HealthVariables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UnitSetup)
	FAttackVariables AttackVariables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UnitSetup)
	FMovementVariables MovementVariables;

	///Gameplay Functions
	//Ability abstract functions
	UFUNCTION(BlueprintCallable, Category = Abilities)
	virtual void Ability_1();

	//General functions
	virtual void OnDeath();
};
