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
	//if (bNewSelection) {
	//	//Update the mouse hit
	//	Parent->GetHitResultUnderCursor(ECC_Visibility, false, RootActorUnderMousePos);

	//	//Check if the hit actor is the type we want - TODO
	//	AActor* temp = GetObjectAtHit<AActor>(RootActorUnderMousePos);
	//	if (temp) {
	//		if (bIsClicking) {
	//			UnClick();
	//			EndSelection();
	//		}
	//	}
	//}
	if (bIsClicking) {
		FHitResult hitty;
		Parent->GetHitResultUnderCursor(ECC_Visibility, false, hitty);

		//Do not register the click unless the clicked actor is AUnit or AStructure
		if(GetObjectAtHit<AUnit>(hitty) || GetObjectAtHit<AStructure>(hitty))
			Parent->ClickedActor = GetObjectAtHit<AActor>(hitty);
		
		Parent->ClickedLocation = hitty.ImpactPoint;

		UnClick();
	}
}

void UClickingComponent::Click()
{
	bIsClicking = true;
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
	bNewSelection = false;
	return ActorBuffer;
}

template <class T>
T* UClickingComponent::GetObjectAtHit(FHitResult hit) {
	return Cast<T>(hit.Actor);
}

template <class T>
T * UClickingComponent::GetObjectAtHitUnderMouseCursor()
{
	FHitResult ParentCursorHit;
	Parent->GetHitResultUnderCursor(ECC_Visibility, false, ParentCursorHit);
	T* TempActor = GetObjectAtHit<T>(ParentCursorHit);
}

FHitActorStats UClickingComponent::GetObjectUnderMouseCursorAttributes()
{
	//Declare the return struct
	FHitActorStats ReturnStats;

	//Get whatever actor is under the mouse cursor
	FHitResult ParentCursorHit;
	Parent->GetHitResultUnderCursor(ECC_Visibility, false, ParentCursorHit);
	AActor* TempActor = GetObjectAtHit<AActor>(ParentCursorHit);

	//Check if it is AUnit or AStructure
	if (AUnit* temp1 = Cast<AUnit>(TempActor)) {
		ReturnStats.ActorType = AUnit::StaticClass();
		
	}
	else if (AStructure* temp2 = Cast<AStructure>(TempActor)) {
		ReturnStats.ActorType = AStructure::StaticClass();
		ReturnStats.ActorLocation = temp2->GetActorLocation();
		ReturnStats.ActorStatus = temp2->GetStatusToPlayer();
	}
	else {
		ReturnStats.ActorType = NULL;
		ReturnStats.ActorLocation = ParentCursorHit.ImpactPoint;
		ReturnStats.ActorStatus = EStatusToPlayer::STP_None;
	}

	ReturnStats.HitActor = TempActor;

	return ReturnStats;

}
