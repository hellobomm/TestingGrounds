// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNewWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Public/PatrollingGuard.h"  //TODO remove coupling



EBTNodeResult::Type UChooseNewWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	//UBTTaskNode  is an abstract class, so it has no definitions, only declarations. 
	//That is why Super::ExecuteTask() is not used here
	
	
	//get TP
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	//set next waypoint
	//get blackboard and current index
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	//set the WaypointKey on the blackboard
	BlackboardComp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);

	//TODO protect against empty patrol routes

	//cycle the Index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();   //the mod operator
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	//UE_LOG(LogTemp, Warning, TEXT("waypoints name: %s"), *CurrentWaypoint->GetName())

	return EBTNodeResult::Succeeded;
}