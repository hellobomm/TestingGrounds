// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"


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
	CanSpawnAtLocation(GetActorLocation(), 300);
	CanSpawnAtLocation(GetActorLocation() + FVector(0,0,1000), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn=1, int32 MaxSpawn=1, float Radius=500)
{	
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int32 i = 0; i < NumberToSpawn; i++)
	{ 
		FVector SpawnPoint;
		if (FindEmptyLocation(Radius, SpawnPoint))
		{
			PlaceActor(ToSpawn, SpawnPoint);
		}
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
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(	GetWorld(),
						GlobalLocation,
						0,
						Radius,
						FQuat::Identity,
						ResultColor,
						true,
						100
					);

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
		if (CanSpawnAtLocation(SpawnPoint, 300)) return true;
	}
	//nothing found...
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	FRotator SpawnRotation = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);
	Spawned->SetActorRelativeRotation(SpawnRotation);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}