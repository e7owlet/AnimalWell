// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "DoorActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API ADoorActor : public ABasePropActor
{
	GENERATED_BODY()

	public:
	//构造函数
	ADoorActor();

	//开关1生成点
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	FVector Ta1Vector;
	//开关1指针
	UPROPERTY()
	class AToggerActor * TA1;
	//开关2生成点
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	FVector Ta2Vector;
	//开关2指针
	UPROPERTY()
	class AToggerActor * TA2;
	//开关3生成点
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	FVector Ta3Vector;
	//开关3指针
	UPROPERTY()
	class AToggerActor * TA3;
	//渲染资产组件
	class UPaperSpriteComponent * DoorSpriteComp;
	//游戏开始时执行
	virtual void BeginPlay() override;
	//重写基类执行函数
	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
};
