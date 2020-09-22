// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ATable;
class AGameManager;
class UInnData;
class FTableSearchRequest;
class ACounter;
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

	void RegisterCounter(ACounter* counter);

	void SaveGame(FString slotName);
	void LoadGame(FString slotName);

	//Dev Functions
	void ClearCurrentTableData();
	void AddTableData(FTableData tableData);

private:
	TArray<ATable*> m_CurrentTables;
	TWeakObjectPtr<AGameManager> m_GameManager;
	UInnData* m_CurrentInnSaveData;
	TSubclassOf<ATable> m_TableClass;
	TWeakObjectPtr<ACounter> m_Counter;
};
