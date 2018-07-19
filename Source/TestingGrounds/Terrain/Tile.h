// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation; 
	float Scale;
};




class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category="Spawning")
	FVector MinExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector NavigationBoundsOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "SetUp")
		void SetActorPool(UActorPool* Actor_Pool);

	UFUNCTION(BlueprintCallable, Category = "SetUp")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "SetUp")
		void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn=1, int32 MaxSpawn=1, float Radius=500);

private:
	UActorPool* ActorPool;
	AActor* NavMeshBoundsVolume;
	bool CanSpawnAtLocation(FVector Location, float Radius);
	bool FindEmptyLocation(float Radius, FVector& SpawnPoint);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition SpawnPosition);
	void PlaceAIPawn(TSubclassOf<APawn> ToSpawn, const FSpawnPosition SpawnPosition);
	void PositionNavMeshBoundsVolume();
	TArray<FSpawnPosition> SpawnPositionGenerator(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);
};
 