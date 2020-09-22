// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineDataGraph.h"
#include "StateMachineGraphNode_State.h"
#include "StateMachineGraphNode_Action.h"
#include "StateMachineGraphNode_Logic.h"
#include "Data/StateMachineData.h"
#include "Data/State/StateData.h"

void UStateMachineDataGraph::OnCreated()
{
	Super::OnCreated();
	//SpawnMissingNodes();
}

void UStateMachineDataGraph::OnLoaded()
{
	Super::OnLoaded();
	//UpdatePinConnectionTypes();
	//RemoveUnknownSubNodes();
}

void UStateMachineDataGraph::OnSave()
{
	UpdateAsset();
}

void UStateMachineDataGraph::Initialize()
{
	Super::Initialize();
	//UpdateInjectedNodes();
}

void UStateMachineDataGraph::OnSubNodeDropped()
{
	Super::OnSubNodeDropped();
}

void UStateMachineDataGraph::UpdateAsset(int32 UpdateFlags /* = 0 */)
{
	//Clean up outer
	UStateMachineData* smAsset = Cast<UStateMachineData>(GetOuter());
	smAsset->States.Empty();


	for (int32 i = 0; i < Nodes.Num(); ++i)
	{
		UStateMachineGraphNode_State* stateNode = Cast<UStateMachineGraphNode_State>(Nodes[i]);

		if (stateNode == nullptr)
		{
			// ignore non state node right now
			continue;
		}

		UStateData* stateData = Cast<UStateData>(stateNode->NodeInstance);
		if (stateData != nullptr)
		{
			smAsset->States.Add(stateData);
		}
	}
}

void UStateMachineDataGraph::MarkVersion()
{

}

void UStateMachineDataGraph::UpdateVersion()
{

}