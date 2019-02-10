// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/Enumuri.h"
#include "Structure.generated.h"

class AUnit;

UCLASS()
class GAMECELERATOR_V1_API AStructure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStructure();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	STATUS statusToPlayer;

	float Health;
	bool isClicked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StructureMesh;

	UPROPERTY(EditAnywhere)
	FVector SpawningOffset;

	UFUNCTION(BlueprintCallable, Category = "SunShine")
	void SpawnUnit(TSubclassOf<AUnit> unitclass);

public:
	bool trainUnit();
	void showInterface();
};
