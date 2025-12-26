// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractionPropComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANIMALWELL_API UInteractionPropComponent : public USceneComponent
{
	GENERATED_BODY()
	//角色指针
	class ACharacter* CharacterInstance;
	//胖猪数量
	int32 FirecrackerCount = 0;
	//判断是否按下A键
	bool bPressA;
	//判断是否按下B键
	bool bPressD;
	
public:	
	// 初始化组件 默认自带
	UInteractionPropComponent();

protected:
	// 游戏开始时执行
	virtual void BeginPlay() override;
	
public:
	//爆竹的UI页面指针
	UPROPERTY(VisibleAnywhere)
	class UFirecrackerUserWidget *FirecrackerWidget;
	//组件每帧自动调用
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//向前检测开关
	void TracePropForword();
	//像后检测开关
	void TracePropBack();
	//检测开关，爆竹，蜡烛
	void TracePropToggleAndFirecrackerAndCandle();
	//按下按键执行时间 记录AD按键的按下与抬起
	void BindKeyDownEvent();
	//现实爆竹数量
	void  ShowFirecrackerCount();
	
};
