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
	void SpawnSelectedObject();

	void EnterConstructMode();
	void ExitConstructMode();

	void Tick();

	void UpdateConstructMode();

	void SaveGame(FString slotName);
	void LoadGame(FString slotName);
	void ResetSaveData();

	void SetSelectedClass(TSubclassOf<AConstructableObject> objectClass);
	TSubclassOf<AConstructableObject> LoadClassViaTypeAndLevel(EConstructableObjectType objectType, int level);
	void SetCurrentLayer(int layerNumber);

	EInnManagerMode GetInnManagerMode() const { return m_CurrentMode; }

	void SpawnFromSavedData();
	void SaveObjectsData();

	//Dev Function
	void OrganizeBaseBlocks();

private:
	void UpdateSelectedBaseBlock();

	TArray<ATable*> m_CurrentTables;
	TWeakObjectPtr<AGameManager> m_GameManager;
	UInnData* m_CurrentInnSaveData;
	TSubclassOf<ATable> m_TableClass;
	TSubclassOf<AFloorBlock> m_FloorBlockClass;
	ACounter* m_Counter;
	EInnManagerMode m_CurrentMode;

	TSubclassOf<AConstructableObject> m_CurrentSelectedClass;
	ABaseBlock* m_StartBaseBlock;
	ABaseBlock* m_EndBaseBlock;

	TArray<ABaseBlock*> m_CurrentSelectedBaseBlocks;
	TMap<FBlockCoordinate, ABaseBlock*> m_ConstructBaseBlockMap;
	AConstructableObject* m_CurrentDisplayObject;

	TArray<AConstructableObject*> m_CurrentObjects;

	UDataTable* m_AssetDataTable;

	int m_CurrentLayerNumber;
	int m_CurrentObjectLevel;
	EConstructableObjectType m_CurrentObjectType;

#ifdef WITH_EDITOR
	TArray<ABaseBlock*> m_BaseBlocks;
#endif
};
