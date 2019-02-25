// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Public/Enumuri.h"
#include "Unit.generated.h"

UENUM(BlueprintType)
enum class EStatusToPlayer : uint8
{
	STP_Friendly	UMETA(DisplayName = "Friendly"),
	STP_Neutral		UMETA(DisplayName = "Neutral"),
	STP_Hostile		UMETA(DisplayName = "Hostile")
};

USTRUCT(BlueprintType)
struct FSetupVariables
{
	GENERATED_USTRUCT_BODY()

	//Relationship between player and unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatusToPlayer status;

	//Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
		float HealthMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float Health;

	UPROPERTY(VisibleAnywhere, Category = Damage)
		float DamagePerHit;

	UPROPERTY(VisibleAnywhere, Category = Damage)
		float TimeBetweenHits;

	UPROPERTY(VisibleAnywhere, Category = Damage)
		float AttackRange;

	UPROPERTY(EditAnywhere, Category = Movement)
		float WalkingSpeed;
};

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
	EStatusToPlayer getStatusToPlayer();

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
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isSelected;

	//setup variables such as health, damage, etc
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UnitSetup)
	FSetupVariables SetupVariables;
};
