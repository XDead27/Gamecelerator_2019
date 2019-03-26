// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceStructure.h"
#include "TreeStructure.generated.h"

class UInstancedStaticMeshComponent;
class UActorComponent;

/**
 * 
 */
UCLASS()
class GAMECELERATOR_V1_API ATreeStructure : public AResourceStructure
{
	GENERATED_BODY()
	
public:
	ATreeStructure();

	//Meshes
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Trees)
	class UInstancedStaticMeshComponent* Trees;
	UPROPERTY(BlueprintREadWrite, EditAnywhere, Category = Trees)
	int NumberOfTreesRow;
	UPROPERTY(BlueprintREadWrite, EditAnywhere, Category = Trees)
	int NumberOfTreesColumn;*/

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TreesS)
	//class UActorComponent* Trees;

};
