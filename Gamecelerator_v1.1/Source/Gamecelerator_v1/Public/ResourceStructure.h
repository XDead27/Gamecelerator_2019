// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructurePrimitive.h"
#include "Public/Enumuri.h"
#include "ResourceStructure.generated.h"

class UStaticMeshComponent;

/**
 * 
 */

UCLASS()
class GAMECELERATOR_V1_API AResourceStructure : public AStructurePrimitive
{
	GENERATED_BODY()

public:
	AResourceStructure();

protected:
	virtual void BeginPlay() override;

public:
	//Stats
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EResourceType ResourceType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ResourcesMax;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int ResourcesLeft;

	//For gather function
	int GetHarvested(int Amount);
	int GetResourcesLeft();
};
