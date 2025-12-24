// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePropActor.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GhostActor.generated.h"

//用枚举表示蓝鬼状态
UENUM()
enum class EGhostState : uint8
{
	Idle,
	Walk,
	Jump,
	Dash
};

UCLASS()
class ANIMALWELL_API AGhostActor : public ABasePropActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGhostActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//渲染资产组件
	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* RenderGhost;
	//渲染资产
	UPROPERTY(EditAnywhere,Category = "Ghost|Animation")
	UPaperFlipbook* GhostFlipbook_Idle;
	UPROPERTY(EditAnywhere,Category = "Ghost|Animation")
	UPaperFlipbook* GhostFlipbook_Walk;
	UPROPERTY(EditAnywhere,Category = "Ghost|Animation")
	UPaperFlipbook* GhostFlipbook_Jump;
	UPROPERTY(EditAnywhere,Category = "Ghost|Animation")
	UPaperFlipbook* GhostFlipbook_Dash;

	//胶囊体碰撞, 用于拾取和爆炸的检测
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* GhostCollisionComponent;

	//移动组件
	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> MyMovementComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	//记录蓝鬼当前状态
	UPROPERTY()
	EGhostState CurrentGhostState;
	//修改蓝鬼状态
	void ChangeGhostState(EGhostState NewGhostState);
	UPaperFlipbook* GetGhostFlipbook(EGhostState GhostState);

	//基类的响应函数

	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
	//更新位置
	UFUNCTION()
	void UpdateTargetLocation();
	//移动函数
	void GhostMove(FVector Destination);
	UPROPERTY()
	int32 MoveDirection;
	//该变量应该存储一个player类的target来动态获取，此处取一个默认值作为测试
	UPROPERTY()
	FVector TargetLocation;
	void UpdateGhostState();
};
