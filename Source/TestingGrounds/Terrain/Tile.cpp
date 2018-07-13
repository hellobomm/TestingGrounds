// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"


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
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->SetActorRelativeRotation(SpawnRotation);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
	
}

