// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNewWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"



EBTNodeResult::Type UChooseNewWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	//UBTTaskNode  is an abstract class, so it has no definitions, only declarations. 
	//That is why Super::ExecuteTask() is not used here
	
	

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	UE_LOG(LogTemp,Warning,TEXT("Waypoint: %i"),Index)

	


	return EBTNodeResult::Succeeded;
}