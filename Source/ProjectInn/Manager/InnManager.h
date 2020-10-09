// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SharedEnumTypes.h"
#include "InteractableObjects/Inn/BaseBlock.h"

class ATable;
class AGameManager;
class UInnData;
class FTableSearchRequest;
class ACounter;
class AFloorBlock;
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
	void SpawnSelectedObject();

	void EnterConstructMode();
	void ExitConstructMode();

	void Tick();

	void UpdateConstructMode();

	void RegisterCounter(ACounter* counter);

	void AddSelectedBaseBlock(ABaseBlock* block);

	void SaveGame(FString slotName);
	void LoadGame(FString slotName);

	UMaterial* LoadFloorBlockAssetMat(EFloorBlockMaterial blockMat);

	void SetSelectedClass(TSubclassOf<AConstructableObject> objectClass);

	//Dev Functions
	void ClearCurrentTableData();
	void AddTableData(FTableData tableData);

	void OnLeftBtnPressed();

	EInnManagerMode GetInnManagerMode() const { return m_CurrentMode; }

	void OrganizeBaseBlocks();

private:
	void UpdateSelectedBaseBlock();

	TArray<ATable*> m_CurrentTables;
	TWeakObjectPtr<AGameManager> m_GameManager;
	UInnData* m_CurrentInnSaveData;
	TSubclassOf<ATable> m_TableClass;
	TSubclassOf<AFloorBlock> m_FloorBlockClass;
	TWeakObjectPtr<ACounter> m_Counter;
	EInnManagerMode m_CurrentMode;

	TSubclassOf<AConstructableObject> m_CurrentSelectedClass;
	ABaseBlock* m_StartBaseBlock;
	ABaseBlock* m_EndBaseBlock;

	TArray<ABaseBlock*> m_CurrentSelectedBaseBlocks;
	TMap<FBlockCoordinate, ABaseBlock*> m_ConstructBaseBlockMap;
	AConstructableObject* m_CurrentDisplayObject;

#ifdef WITH_EDITOR
	TArray<ABaseBlock*> m_BaseBlocks;
#endif
};
