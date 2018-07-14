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
	CastSphere(GetActorLocation(), 300);
	CastSphere(GetActorLocation() + FVector(0,0,1000), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn)
{	
	FVector Min(0, -2000, 0);
	FVector Max{4000,2000,0 };
	FBox Bounds(Min, Max);

	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int32 i = 0; i < NumberToSpawn; i++)
	{ 
		FRotator SpawnRotation = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f),0.0f);
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);

		//TODO Check with CastSphere if location is free
		//CastSphere(Spawned->GetActorLocation(), 300);

		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->SetActorRelativeRotation(SpawnRotation);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
	
}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(	HitResult,
													Location,
													Location,
													FQuat::Identity,
													ECollisionChannel::ECC_GameTraceChannel2,
													FCollisionShape::MakeSphere(Radius)
												);
	//ui!!! Lecture 311  
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(	GetWorld(),
						Location,
						0,
						Radius,
						FQuat::Identity,
						ResultColor,
						true,
						100
					);

	return HasHit;
}

