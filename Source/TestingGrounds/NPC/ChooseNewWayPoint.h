// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNewWayPoint.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API UChooseNewWayPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		FBlackboardKeySelector IndexKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
		FBlackboardKeySelector WayPointKey;

private:

	int32 IndexOfCurrentWaypoint=0;


};
 