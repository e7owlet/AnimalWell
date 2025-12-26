// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Actors/BasePropActor.h"
#include "LightActor.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API ALightActor : public ABasePropActor
{
	GENERATED_BODY()

	
public:
	
	//灯的构造函数
	ALightActor();

protected:
	// 游戏开始时执行
	virtual void BeginPlay() override;
	//等线的渲染组件
	class UPaperSpriteComponent* LineSpriteComp;
	//灯泡的渲染组件
	class UPaperSpriteComponent* LightSpriteComp;
	//碰撞后旋转角度的目标值
	FRotator TargetRotator;
	//移动速率曲线
	FFloatCurve* MoveCurve;
public:	
	// Actor每帧执行函数
	virtual void Tick(float DeltaTime) override;
	// 触发交互函数
	virtual void ActionEvent(FVector BeginLoaction) override;
	// 构造脚本函数
	virtual void OnConstruction(const FTransform& Transform) override;
	//光照通道设置
	UPROPERTY(EditAnywhere)
	FName MName;

	// 钟摆核心变量
	float CurrentAngle;// 当前角度
	float CurrentSpeed;// 当前速度
	float MaxSwingAngle = 30.f;     // 最大摆动角度
    //
	float SwingAngle;   // 当前角度
	float SwingSpeed;   // 当前速度
    
	

	
};
