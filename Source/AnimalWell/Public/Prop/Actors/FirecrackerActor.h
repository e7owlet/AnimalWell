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
	// Sets default values for this actor's properties
	// 构造函数
	AFirecrackerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//渲染资产组件
	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* FirecrackerSpriteComp;
	//渲染资产
	UPROPERTY(EditAnywhere)
	class UPaperSprite* FirecrackerSprite;

	//胶囊体碰撞, 用于拾取和爆炸的检测
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* FirecrackerCollisionComponent;

	//抛物线运动组件
	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> MyProjectileMovementComp;
	//空中翻转组件
	UPROPERTY(EditAnywhere)
	TObjectPtr<URotatingMovementComponent> MyRotatingMovementComp;

	UPROPERTY()
	FTimerHandle CrackerHandle;

	void DestroyFirecracker();

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	//基类的响应函数
	virtual void ActionEvent(FVector BeginLoaction = FVector::ForwardVector * -1) override;
	
};
