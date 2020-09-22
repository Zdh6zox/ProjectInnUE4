// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Recipe/Recipe.h"

/**
 * 
 */
class PROJECTINN_API FDish
{
private:
	TWeakPtr<FRecipe> m_BaseRecipe;
	TArray<FFlavour> m_Flavours;
};
