// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePropActor.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "FirecrackerActor.generated.h"

UCLASS()
class ANIMALWELL_API AFirecrackerActor : public ABasePropActor
{
	GENERATED_BODY()

public:
	//构造函数
	AFirecrackerActor();

protected:
	// 游戏开始时执行
	virtual void BeginPlay() override;
	//显然组件
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* FirecrackerSpriteComp;
	//渲染资产
	UPROPERTY(EditAnywhere)
	class UPaperSprite* FirecrackerSprite;
	//碰撞检测组件
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* FirecrackerCollisionComponent;
	//移动组件
	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> MyProjectileMovementComp;
	//旋转组件
	UPROPERTY(EditAnywhere)
	TObjectPtr<URotatingMovementComponent> MyRotatingMovementComp;
	//定时器任务
	UPROPERTY()
	FTimerHandle CrackerHandle;
	//销毁函数
	void DestroyFirecracker();

public:
	
	// 每帧调用
	virtual void Tick(float DeltaTime) override;
	// 构造脚本
	virtual void OnConstruction(const FTransform& Transform) override;

	//基类执行函数重写
	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
	
};
