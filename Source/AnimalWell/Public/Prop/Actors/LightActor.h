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
	
	// Sets default values for this actor's properties
	ALightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UPaperSpriteComponent* LineSpriteComp;
	class UPaperSpriteComponent* LightSpriteComp;
	FRotator TargetRotator;
	FFloatCurve* MoveCurve;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ActionEvent(FVector BeginLoaction) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	

	// 钟摆核心变量
	float CurrentAngle;     // 当前角度
	float CurrentSpeed;     // 当前速度
	float MaxSwingAngle = 30.f;    // 最大摆动角度
    
	float SwingAngle;   // 当前角度
	float SwingSpeed;   // 当前速度
    
	

	
};
