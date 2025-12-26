// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "CandleActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API ACandleActor : public ABasePropActor
{
	GENERATED_BODY()
	//蜡烛状态
	bool OpenFlag;
public:
	//构造函数
	ACandleActor();
	//获取蜡烛点燃状态
	bool GetOpenFlag(){ return OpenFlag; };
	//获取蜡烛点燃状态
	void SetOpenFlag(bool InOpenFlag){ OpenFlag = InOpenFlag; };
	//游戏开始时执行
	virtual void BeginPlay() override;
	//渲染组件
	class UPaperSpriteComponent *SpriteComp;
	//重写基类触发函数
	void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
};
