// Fill out your copyright notice in the Description page of Project Settings.


#include "SMTransitionSchema.h"
#include "SMTransitionGraph.h"

#define LOCTEXT_NAMESPACE "SMTransitionSchema"

USMTransitionSchema::USMTransitionSchema(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Initialize defaults
}

void USMTransitionSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	//// Create the entry/exit tunnels
	//FGraphNodeCreator<UAnimGraphNode_TransitionResult> NodeCreator(Graph);
	//UAnimGraphNode_TransitionResult* ResultSinkNode = NodeCreator.CreateNode();
	//NodeCreator.Finalize();
	//SetNodeMetaData(ResultSinkNode, FNodeMetadata::DefaultGraphNode);

	//USMTransitionGraph* TypedGraph = CastChecked<USMTransitionGraph>(&Graph);
	//TypedGraph->MyResultNode = ResultSinkNode;
}

void USMTransitionSchema::GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const
{

}

void USMTransitionSchema::HandleGraphBeingDeleted(UEdGraph& GraphBeingRemoved) const
{

}
#undef LOCTEXT_NAMESPACE