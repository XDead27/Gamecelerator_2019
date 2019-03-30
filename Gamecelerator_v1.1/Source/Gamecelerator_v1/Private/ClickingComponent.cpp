// Fill out your copyright notice in the Description page of Project Settings.

#include "ClickingComponent.h"
#include "Public/PlayerSpectatorPawnController.h"

// Sets default values for this component's properties
UClickingComponent::UClickingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UClickingComponent::BeginPlay()
{
	Super::BeginPlay();

	Parent = Cast<APlayerSpectatorPawnController>(this->GetOwner());
}


// Called every frame
void UClickingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If the selection sequence is on
	if (bNewSelection) {
		//Update the mouse hit
		Parent->GetHitResultUnderCursor(ECC_Visibility, false, RootActorUnderMousePos);

		//Check if the hit actor is the type we want - TODO
		AActor* temp = GetObjectAtHit<AActor>(RootActorUnderMousePos);
		if (temp-StaticClass()->IsChildOf(ActorToSearch->StaticClass())){
			ActorBuffer = temp;
			if (bIsClicking) {
				UnClick();
				Parent->ClickedActor = EndSelection();
			}

			UE_LOG(LogTemp, Warning, TEXT("yosh"))
		}
		else if(bIsClicking) {
			UE_LOG(LogTemp, Warning, TEXT("This is not an actor of the specified class"))
			UnClick();
		}
	}
}

void UClickingComponent::Click()
{
	bIsClicking = true;
	if (!bNewSelection) {
		FHitResult hitty;
		Parent->GetHitResultUnderCursor(ECC_Visibility, false, hitty);
		Parent->ClickedActor = GetObjectAtHit<AActor>(hitty);
	}
}

void UClickingComponent::UnClick()
{
	bIsClicking = false;
}

void UClickingComponent::NewSelection(TSubclassOf<AActor> ClassToSearch)
{
	bNewSelection = true;
	ActorToSearch = ClassToSearch;
}

AActor * UClickingComponent::EndSelection()
{
	return ActorBuffer;
}

template <class T>
T* UClickingComponent::GetObjectAtHit(FHitResult hit) {
	return Cast<T>(hit.Actor);
}