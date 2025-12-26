// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/ToggerActor.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Prop/Actors/DoorActor.h"

AToggerActor::AToggerActor()
{
	//创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root0"));
	//创建渲染组件
	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp0"));
	//把渲染组件绑定到根组件上
	SpriteComp->SetupAttachment(RootComponent);
	//设置碰撞预设
	SpriteComp->SetCollisionProfileName(TEXT("Prop"));
}

void AToggerActor::BeginPlay()
{
	Super::BeginPlay();
	//游戏开始时加载资产
	UPaperSprite * CloseToggle = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_ToggleClose.PS_ToggleClose'"));
	//给渲染组件设置资产
	SpriteComp->SetSprite(CloseToggle);
}

void AToggerActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);
	//标记开关为打开状态
	OpenFlag = true;
	//加载开关开启资产
	UPaperSprite * OpenToggle = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_ToggleOpen.PS_ToggleOpen'"));
	//设置开关打开资产
	SpriteComp->SetSprite(OpenToggle);
	//同质门的开关逻辑
	Cast<ADoorActor>(GetOwner())->ActionEvent(BeginLoaction);
}
