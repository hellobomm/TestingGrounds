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
