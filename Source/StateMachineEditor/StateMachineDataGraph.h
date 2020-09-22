// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/AIGraph/Classes/AIGraph.h"
#include "StateMachineDataGraph.generated.h"

/**
 * 
 */
UCLASS()
class STATEMACHINEEDITORMODULE_API UStateMachineDataGraph : public UAIGraph
{
	GENERATED_BODY()

public:
	enum EUpdateFlags
	{
		RebuildGraph = 0,
		ClearDebuggerFlags = 1,
		KeepRebuildCounter = 2,
	};

	virtual void OnCreated() override;
	virtual void OnLoaded() override;
	void OnSave();
	virtual void Initialize() override;

	virtual void UpdateVersion() override;
	virtual void MarkVersion() override;
	virtual void UpdateAsset(int32 UpdateFlags = 0) override;
	virtual void OnSubNodeDropped() override;
	
};
