// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "AnimalWellPaperSpriteComponent.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API UAnimalWellPaperSpriteComponent : public UPaperSpriteComponent
{
	GENERATED_BODY()
public:
	void SetScaleParameterValueOnMaterials(const FName ParameterName, const float ParameterValue);
};
