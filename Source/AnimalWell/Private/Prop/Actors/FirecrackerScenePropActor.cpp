// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/FirecrackerScenePropActor.h"

#include "PaperSpriteComponent.h"

AFirecrackerScenePropActor::AFirecrackerScenePropActor()
{
	//创建根组件渲染
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	//创建渲染组件对象
	FirecrackerSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>("FirecrackerSpriteComp");
	//绑定到根组件
	FirecrackerSpriteComp->SetupAttachment(this->RootComponent);
	//设置场景内显示的大小
	FirecrackerSpriteComp->SetRelativeScale3D(FVector(0.12f));
	//设置碰撞预设为Prop
	FirecrackerSpriteComp->SetCollisionProfileName(TEXT("Prop"));
}

void AFirecrackerScenePropActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);
	// 如果被拾取到，销毁场景道具
	Destroy();
}
void AFirecrackerScenePropActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//如果没有加载资产
	if (!FirecrackerSprite)
	{
		//加载资产对象
		FirecrackerSprite = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Cracker.PS_Cracker'"));
	}
	//如果已经加载资产
	if (FirecrackerSprite)
	{
		//把资产设置到渲染组件
		FirecrackerSpriteComp->SetSprite(FirecrackerSprite);
	}
}