// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNewWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"



EBTNodeResult::Type UChooseNewWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	//UBTTaskNode  is an abstract class, so it has no definitions, only declarations. 
	//That is why Super::ExecuteTask() is not used here
	

	//get PatrolRouteComponent of OwningPawn
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrolRouteComponent = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRouteComponent)) { return EBTNodeResult::Failed; };

	//warn about empty patrol routes
	auto PatrolPoints = PatrolRouteComponent->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) UE_LOG(LogTemp, Warning, TEXT("A Guard misses PatrolPoints"));

	//set next waypoint
	//get blackboard and current index
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	//set the WaypointKey on the blackboard
	BlackboardComp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);


	//cycle the Index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();   //the mod operator
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);


	return EBTNodeResult::Succeeded;
}