// Fill out your copyright notice in the Description page of Project Settings.

#include "TreeStructure.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/ActorComponent.h"

ATreeStructure::ATreeStructure() {
	ResourceType = EResourceType::RT_Wood;

	////NumberOfTreesRow = 3;
	////NumberOfTreesColumn = 3;

	//Trees = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Instanced Trees"));
	//Trees->AttachTo(RootComponent);
	//Trees->RegisterComponent();
	//Trees->SetFlags(RF_Transactional);
	//Trees->SetStaticMesh(BaseMesh->GetStaticMesh());
	//this->AddInstanceComponent(Trees);

	/////Make the instances / the trees
	//FTransform BaseTransform;
	//FVector BaseMin, BaseMax;
	//BaseMesh->UpdateBounds();
	//FVector BaseDimensions = BaseMesh->CalcBounds(BaseTransform).BoxExtent;

	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), BaseDimensions.X, BaseDimensions.Y, BaseDimensions.Z)

	//FTransform TreeTransform;
	//for (int i = 1; i <= NumberOfTreesRow; i++) {
	//	float XSpacing = (BaseDimensions.X / (NumberOfTreesRow + 1)) * i;
	//	for (int f = 1; f <= NumberOfTreesColumn; f++) {
	//		float YSpacing = (BaseDimensions.Y / (NumberOfTreesColumn + 1)) * f;
	//		TreeTransform.SetTranslation(FVector(XSpacing, YSpacing, BaseDimensions.Z));
	//		TreeTransform.SetRotation(FQuat(0, 0, FMath::RandRange(0, 360), 0));

	//		int h = Trees->AddInstance(TreeTransform);

	//		UE_LOG(LogTemp, Warning, TEXT("%d instance"), h)
	//	}
	//}

	//Trees = CreateDefaultSubobject<UActorComponent>(TEXT("Instanced Trees"));

}