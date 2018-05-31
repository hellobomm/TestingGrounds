// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNewWayPoint.h"




EBTNodeResult::Type UChooseNewWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp,Warning,TEXT("Execute Task"))
	return EBTNodeResult::Succeeded;
}