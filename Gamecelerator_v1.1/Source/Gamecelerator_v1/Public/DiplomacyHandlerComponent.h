// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enumuri.h"
#include "DiplomacyHandlerComponent.generated.h"

class AController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, ShortTooltip = "A Diplomacy Handler Component is just a set of variables because UE4 does not allow multiple inheritance"))
class GAMECELERATOR_V1_API UDiplomacyHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDiplomacyHandlerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Diplomacy)
	int ParentControllerTeamIndex;

	//List of all controllers and this component's parent status with them
	TMap<AController*, EStatusToPlayer> DiplomacyList;
		
};
