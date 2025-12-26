// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "ToggerActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API AToggerActor : public ABasePropActor
{
	GENERATED_BODY()
	//开关的状态
	bool OpenFlag;
	public:
	//构造函数
	AToggerActor();
	//获取开关状态
	bool GetOpenFlag(){ return OpenFlag; };
	//设置开关状态
	void SetOpenFlag(bool InOpenFlag){ OpenFlag = InOpenFlag; };
	//游戏开始时执行
	virtual void BeginPlay() override;
	//渲染组件指针
	UPROPERTY(visibleAnywhere, BlueprintReadWrite)
	class UPaperSpriteComponent *SpriteComp;
	//父类继承的开关触发函数
	void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
};
