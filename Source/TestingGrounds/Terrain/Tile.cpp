// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "ActorPool.h"
#include "Engine/World.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"



// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationBoundsOffset = FVector(2000, 0, 0);

	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
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

void ATile::SetActorPool(UActorPool * Actor_Pool)
{
	ActorPool = Actor_Pool;
	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = ActorPool->CheckOut();

	if (NavMeshBoundsVolume==nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("new Tile [%s] complains: Not enough Actors in pool!"), *GetName())
		return;
	}
	UE_LOG(LogTemp,Warning, TEXT("new Tile [%s] checked out from the pool: %s"), *GetName(),*NavMeshBoundsVolume->GetName())
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation()+ NavigationBoundsOffset);

	//we now have to rebuild the Volume
	GetWorld()->GetNavigationSystem()->Build();
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{	
	TArray<FSpawnPosition>SpawnPositions;
	SpawnPositions = SpawnPositionGenerator(MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);

	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{ 
		PlaceActor(ToSpawn, SpawnPosition);
	}
}

TArray<FSpawnPosition> ATile::SpawnPositionGenerator(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPosition>SpawnPositionArray;
	FSpawnPosition SpawnPosition;
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int32 i = 0; i < NumberToSpawn; i++)
	{
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);

		if (FindEmptyLocation(Radius*SpawnPosition.Scale, SpawnPosition.Location))
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.0f, 180.0f);
			SpawnPositionArray.Add(SpawnPosition);
		};
	}
	return SpawnPositionArray;
}

bool ATile::FindEmptyLocation(float Radius, FVector& SpawnPoint)
{
	FBox Bounds(MinExtent, MaxExtent);

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
	
	//if (!HasHit)
	//{
	//	DrawDebugCapsule(GetWorld(),
	//		GlobalLocation,
	//		0,
	//		Radius,
	//		FQuat::Identity,
	//		ResultColor,
	//		true,
	//		100
	//	);
	//}
	

	return !HasHit;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->SetActorRotation(FRotator(0.0f, SpawnPosition.Rotation, 0.0f));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	UE_LOG(LogTemp, Warning, TEXT("Tile [%s] returned to pool: %s"), *GetName(), *NavMeshBoundsVolume->GetName())
	ActorPool->Return(NavMeshBoundsVolume);
}
