// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/DoorActor.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Prop/Actors/ToggerActor.h"

ADoorActor::ADoorActor()
{
	//创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp0"));
	//创建渲染组件
	DoorSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DoorSpriteComp0"));
	//渲染组件绑定到跟组件上
	DoorSpriteComp->SetupAttachment(RootComponent);
	//设置们可以阻挡任何人
	DoorSpriteComp->SetCollisionProfileName(TEXT("BlockAll"));
}

void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	//游戏开始时 创建开关1
	TA1 = GetWorld()->SpawnActor<AToggerActor>(GetActorLocation()+Ta1Vector,FRotator(0));
	//游戏开始时 设置开关1的所有者为当前的门
	TA1->SetOwner(this);
	//游戏开始时 创建开关2
	TA2 = GetWorld()->SpawnActor<AToggerActor>(GetActorLocation()+Ta2Vector,FRotator(0));
	//游戏开始时 设置开关2的所有者为当前的门
	TA2->SetOwner(this);
	//游戏开始时 创建开关3
	TA3 = GetWorld()->SpawnActor<AToggerActor>(GetActorLocation()+Ta3Vector,FRotator(0));
	//游戏开始时 设置开关3的所有者为当前的门
	TA3->SetOwner(this);
	//加载并设置关门资产
	DoorSpriteComp->SetSprite(LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_DoorClose.PS_DoorClose'")));
}
void ADoorActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);
	//三个开关如果都为打开，更换门的资产和设置们可以穿过
	if (TA1->GetOpenFlag() && TA2->GetOpenFlag() && TA3->GetOpenFlag())
	{
		//加载并设置开门资产
		DoorSpriteComp->SetSprite(LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Open.PS_Open'")));
		//设置们的碰撞为没有碰撞
		DoorSpriteComp->SetCollisionProfileName(TEXT("NoCollision"));
	}
	
	
}

