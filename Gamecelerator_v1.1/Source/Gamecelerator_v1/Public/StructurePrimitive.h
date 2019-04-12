// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RacePrimitive.h"
#include "StructurePrimitive.generated.h"

class UBoxComponent;

UCLASS()
class GAMECELERATOR_V1_API AStructurePrimitive : public AActor, public IRacePrimitive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStructurePrimitive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//The basic box collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	bool bDisableBoxCollision; //TODO

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* StructureMesh;
};
