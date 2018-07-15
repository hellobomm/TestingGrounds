// Fill out your copyright notice in the Description page of Project Settings.

#include "GrassComponent.h"



// Sets default values for this component's properties
UGrassComponent::UGrassComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();
	CreateInstances();

	// ...


	////look for UHierarchicalInstancedStaticMeshComponent in the components
	//TArray<UActorComponent*> HIMCs;
	//HIMCs = GetComponentsByClass(UHierarchicalInstancedStaticMeshComponent::StaticClass());

	//for (int32 i = 0; i<HIMCs.Num(); i++)
	//{
	//	UHierarchicalInstancedStaticMeshComponent* TempHIMC = Cast<UHierarchicalInstancedStaticMeshComponent>(HIMCs[i]);

	//	for (int32 j = 0; j < int32 MaxNumberOfInstances; j++)
	//	{
	//		FVector Min(0, -2000, 0);
	//		FVector Max{ 4000,2000,0 };
	//		FBox Area(Min, Max);

	//		FTransform InstanceTransform;
	//		InstanceTransform.SetLocation(FMath::RandPointInBox(Area));
	//		InstanceTransform.SetRotation(FQuat(GetActorUpVector(), FMath::RandRange(-180.0f, 180.0f)));
	//		TempHIMC->AddInstance(InstanceTransform);
	//	}
	//}
	
}


// Called every frame
void UGrassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrassComponent::CreateInstances()
{
	for (int32 j = 0; j < SpawnCount; j++)
	{
		FTransform InstanceTransform;
		InstanceTransform.SetLocation(FMath::RandPointInBox(SpawningExtents));
		InstanceTransform.SetRotation(FQuat(FVector(0,0,1), FMath::RandRange(-180.0f, 180.0f)));
		AddInstance(InstanceTransform);
	}
}
