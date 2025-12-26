// Fill out your copyright notice in the Description page of Project Settings.
#include "Prop/Actors/CandleActor.h" // Debug前置
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Kismet/GameplayStatics.h"
#include "Prop/Actors/GhostActor.h"



ACandleActor::ACandleActor()
{
	//创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root0"));
	//创建渲染组件
	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp0"));
	//绑定渲染组件到根组件上
	SpriteComp->SetupAttachment(RootComponent);
	
}

void ACandleActor::BeginPlay()
{
	Super::BeginPlay();
	//游戏开始时加载为点亮蜡烛资产
	UPaperSprite * Candle = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/Mediavel_Sprite.Mediavel_Sprite'"));
	//设置渲染组件资产
	SpriteComp->SetSprite(Candle);
	//设置资检测为场景交互道具
	SpriteComp->SetCollisionProfileName(TEXT("Prop"));
	//设置父提供碰撞组件组件为可交互道具
	CollisionBox->SetCollisionProfileName(TEXT("Prop"));
}

void ACandleActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);
	//点燃蜡烛状态
	OpenFlag = true;
	//加载点燃蜡烛资产
	UPaperSprite * CandleFire = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/MediavelFree_Sprite.MediavelFree_Sprite'"));
	//设置渲染组件
	SpriteComp->SetSprite(CandleFire);
	//查找地图中的蓝鬼对象
	AGhostActor* Ghost = Cast<AGhostActor>( UGameplayStatics::GetActorOfClass(this,AGhostActor::StaticClass()));
    if (Ghost)
    {
    	//销毁蓝鬼
    	Ghost->Destroy();
    }
}
