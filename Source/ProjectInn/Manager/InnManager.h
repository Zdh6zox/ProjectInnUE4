// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SharedEnumTypes.h"

class ATable;
class AGameManager;
class UInnData;
class FTableSearchRequest;
class ACounter;
class AFloorBlock;
class ABaseBlock;
class UMaterial;
class AConstructableObject;
struct FTableData;
/**
 * 
 */
class PROJECTINN_API FInnManager
{
public:
	void InitializeManager(AGameManager* gm);

	void SpawnTables();
	ATable* FindTable(FTableSearchRequest request);
	ACounter* FindCounter();

	void SpawnFloorBlock();

	void EnterConstructMode();
	void ExitConstructMode();

	void Tick();

	void UpdateConstructMode();

	void RegisterCounter(ACounter* counter);

	void SaveGame(FString slotName);
	void LoadGame(FString slotName);

	UMaterial* LoadFloorBlockAssetMat(EFloorBlockMaterial blockMat);

	void SetSelectedClass(TSubclassOf<AConstructableObject> objectClass);

	//Dev Functions
	void ClearCurrentTableData();
	void AddTableData(FTableData tableData);

private:
	TArray<ATable*> m_CurrentTables;
	TArray<ABaseBlock*> m_BaseBlocks;
	TWeakObjectPtr<AGameManager> m_GameManager;
	UInnData* m_CurrentInnSaveData;
	TSubclassOf<ATable> m_TableClass;
	TSubclassOf<AFloorBlock> m_FloorBlockClass;
	TWeakObjectPtr<ACounter> m_Counter;
	EInnManagerMode m_CurrentMode;

	TSubclassOf<AConstructableObject> m_CurrentSelectedClass;
	AConstructableObject* m_CurrentDisplayObject;
};
