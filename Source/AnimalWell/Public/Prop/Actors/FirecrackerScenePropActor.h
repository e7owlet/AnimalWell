// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "FirecrackerScenePropActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API AFirecrackerScenePropActor : public ABasePropActor
{
	GENERATED_BODY()
	public:
	//构造函数
	AFirecrackerScenePropActor();
	//渲染组件
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* FirecrackerSpriteComp;
	//基类触发函数重写
	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
	//构造脚本函数
	virtual  void OnConstruction(const FTransform& Transform);
	//渲染资产设置
	UPROPERTY(EditAnywhere)
	class UPaperSprite* FirecrackerSprite;
};
