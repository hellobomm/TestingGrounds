// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "ActorPool.h"
#include "EngineUtils.h"




AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("ActorPool"));
}


void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	//get all the ANavMeshBoundsVolume Actors of the world and put it in an Iterator
	TActorIterator<ANavMeshBoundsVolume> NavMeshBoundsVolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (NavMeshBoundsVolumeIterator)  //that is how you write this. It looks weird
	{
		AddToPool(*NavMeshBoundsVolumeIterator); //the content is of course the pointer to a NavMeshBoundsVolume
		ANavMeshBoundsVolume* FoundNavMeshBoundsVolume = *NavMeshBoundsVolumeIterator;
		UE_LOG(LogTemp,Warning,TEXT("Found FoundNavMeshBoundsVolume: %s"), *FoundNavMeshBoundsVolume->GetName())
		++NavMeshBoundsVolumeIterator;  //otherwise it won't compile
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume * VolumeToAdd)
{

}
