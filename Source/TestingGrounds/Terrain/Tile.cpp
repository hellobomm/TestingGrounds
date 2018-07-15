// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"



// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{	
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	

	////cast the obejct to spawn into an AActor to get the Method   GetComponents
	//AActor* ObjectToPlace = Cast<AActor>(ToSpawn);
	//TArray<UStaticMeshComponent*> Components;
	//if (!ObjectToPlace) return;
	//ObjectToPlace->GetComponents<UStaticMeshComponent>(Components);
	//
	//Radius = 100;
	//for (int32 i = 0; i < Components.Num(); i++)
	//{	
	//	FVector MinBound;
	//	FVector MaxBound;
	//	Components[i]->GetLocalBounds(MinBound, MaxBound);
	//
	//	if (MinBound.Size() > Radius)Radius = MinBound.Size();
	//	if (MaxBound.Size() > Radius)Radius = MaxBound.Size();
	//}
	

	for (int32 i = 0; i < NumberToSpawn; i++)
	{ 
		FVector SpawnPoint;
		float RandomScale = FMath::RandRange(MinScale, MaxScale);

		if (FindEmptyLocation(Radius*RandomScale, SpawnPoint))
		{
			float SpawnRotation = FMath::RandRange(-180.0f, 180.0f);
			PlaceActor(ToSpawn, SpawnPoint, SpawnRotation, RandomScale);
		};
	}
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(	HitResult,
													GlobalLocation,
													GlobalLocation,
													FQuat::Identity,
													ECollisionChannel::ECC_GameTraceChannel2,
													FCollisionShape::MakeSphere(Radius)
												);
	//ui!!! Lecture 311  
	//FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	FColor ResultColor = FColor::Blue;
	
	if (!HasHit)
	{
		DrawDebugCapsule(GetWorld(),
			GlobalLocation,
			0,
			Radius,
			FQuat::Identity,
			ResultColor,
			true,
			100
		);
	}
	

	return !HasHit;
}

bool ATile::FindEmptyLocation(float Radius, FVector& SpawnPoint)
{
	FVector Min(0, -2000, 0);
	FVector Max{4000,2000,0 };
	FBox Bounds(Min, Max);
	
	//Check with CastSphere if location is free
	const int32 MAX_ATTEMPTS = 100;
	for (int32 i = 0; i < MAX_ATTEMPTS; i++)
	{
		SpawnPoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(SpawnPoint, Radius)) return true;
	}
	//nothing found...
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->SetActorRotation(FRotator(0.0f, Rotation, 0.0f));
	Spawned->SetActorScale3D(FVector(Scale));
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}