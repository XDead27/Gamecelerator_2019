// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structure.h"
#include "Public/Enumuri.h"
#include "ResourceStructure.generated.h"

class UStaticMeshComponent;

/**
 * 
 */




UCLASS()
class GAMECELERATOR_V1_API AResourceStructure : public AActor
{
	GENERATED_BODY()

public:
	AResourceStructure();
	
	//Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BaseMesh)
	class UStaticMeshComponent* BaseMesh;

	//Stats
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EResourceType ResourceType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ResourcesMax;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int ResourcesLeft;
};
