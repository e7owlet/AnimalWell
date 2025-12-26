// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Components/AnimalWellPaperSpriteComponent.h"



void UAnimalWellPaperSpriteComponent::SetScaleParameterValueOnMaterials(const FName ParameterName,const float ParameterValue)
{
	//获取当前材质是否为动态材质实例
	UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(GetMaterial(0));
	//判断是否创建成功
	if (!DynamicMaterial)
	{
		//创建动态材质实例，运行中可以更改材质表现效果
		DynamicMaterial = CreateAndSetMaterialInstanceDynamic(0);
		//设置当前材质实例
		SetMaterial(0,DynamicMaterial);
	}
	//给对应命名的材质实例设置参数
	DynamicMaterial->SetScalarParameterValue(ParameterName, ParameterValue);
}
