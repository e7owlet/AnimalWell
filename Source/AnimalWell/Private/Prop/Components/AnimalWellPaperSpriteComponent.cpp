// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Components/AnimalWellPaperSpriteComponent.h"



void UAnimalWellPaperSpriteComponent::SetScaleParameterValueOnMaterials(const FName ParameterName,const float ParameterValue)
{
	UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(GetMaterial(0));
	
	if (!DynamicMaterial)
	{
		DynamicMaterial = CreateAndSetMaterialInstanceDynamic(0);
		SetMaterial(0,DynamicMaterial);
	}
	DynamicMaterial->SetScalarParameterValue(ParameterName, ParameterValue);
}
