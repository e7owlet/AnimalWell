// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/GhostActor.h"

#include "paperflipbookcomponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGhostActor::AGhostActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	//创建蓝鬼翻书动画渲染组件（帧动画）
	RenderGhost = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("RenderGhostComp"));
	// 绑定到跟组价能上
	RenderGhost->SetupAttachment(RootComponent);
	// 设置蓝鬼大小
	RenderGhost->SetRelativeScale3D(FVector(0.2f));

	//创建胶囊体检测盒
	GhostCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("GhostCollisionComponent");
	//绑定到渲染组件上
	GhostCollisionComponent->SetupAttachment(RenderGhost);
	//设置为可以检测所有物品的重叠
	GhostCollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	//设置胶囊体平面半径
	GhostCollisionComponent->SetCapsuleRadius(72.f);
	//设置胶囊体的半高
	GhostCollisionComponent->SetCapsuleHalfHeight(144.f);
	//游戏中设置可见碰撞区域可视框
	GhostCollisionComponent->bHiddenInGame = false;

	//创建蓝鬼移动组件
	MyMovementComponent  = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	//初始化蓝鬼移动速度
	MyMovementComponent->InitialSpeed = 60.f;
	//设置蓝鬼最大移动速度
	MyMovementComponent->MaxSpeed = 60.f;
	//设置重力对移动的影响
	MyMovementComponent->ProjectileGravityScale = 0.f;
	//设置是否自动激活组件
	MyMovementComponent->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AGhostActor::BeginPlay()
{
	Super::BeginPlay();
	//游戏开始时激活自己事件
	ActionEvent(UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation());
}

// Called every frame
void AGhostActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//更新角色动画状态
	UpdateGhostState();
}

void AGhostActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//如果为Idle,设置角色播放Idle动画
	if (!GhostFlipbook_Idle)
	{
		GhostFlipbook_Idle = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/PF_Ghost_Idle.PF_Ghost_Idle'"));
	}
	//如果为Walk,设置角色播放Walk动画
	if (!GhostFlipbook_Walk)
	{
		GhostFlipbook_Walk = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/PF_Ghost_Walk.PF_Ghost_Walk'"));
	}
	//如果为Jump,设置角色播放Jump动画
	if (!GhostFlipbook_Jump)
	{
		GhostFlipbook_Jump = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/PF_Ghost_Jump.PF_Ghost_Jump'"));
	}
	//如果为Dash,设置角色播放Dash动画
	if (!GhostFlipbook_Dash)
	{
		GhostFlipbook_Dash = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/BlueWizardDash.BlueWizardDash'"));
	}

	//更新播放的动画
	RenderGhost->SetFlipbook(GhostFlipbook_Idle);
}


void AGhostActor::ChangeGhostState(EGhostState NewGhostState)
{
	//修改游戏蓝鬼状态
	CurrentGhostState = NewGhostState;
	//调用根据状态更新动画
	RenderGhost->SetFlipbook(GetGhostFlipbook(CurrentGhostState));
}


UPaperFlipbook* AGhostActor::GetGhostFlipbook(EGhostState GhostState)
{
	//翻书动画指针
	UPaperFlipbook* TempFlipbook = nullptr;

	switch (GhostState)
	{
		case EGhostState::Idle:
			TempFlipbook = GhostFlipbook_Idle;//Idle资产
			break;
		case EGhostState::Walk:
			TempFlipbook = GhostFlipbook_Walk;	//行走资产
			break;
		case EGhostState::Jump:
			TempFlipbook = GhostFlipbook_Jump;//跳跃资产
			break;
		case EGhostState::Dash:
			TempFlipbook = GhostFlipbook_Dash;//冲刺资产
			break;
	}
	return TempFlipbook;
}

void AGhostActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);
	//调用开始移动函数
	GhostMove(BeginLoaction);
}

void AGhostActor::UpdateTargetLocation()
{
	//更新移动线路
	GhostMove(UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation());
}

void AGhostActor::GhostMove(FVector Destination)
{
	ChangeGhostState(EGhostState::Walk);
	//记录目标位置
	TargetLocation = Destination;

	//计算蓝鬼朝向
	MoveDirection = (Destination.X - GetActorLocation().X) > 0 ? 1 : -1;
	//设置蓝鬼朝向
	SetActorRotation(FRotator(0.f, (Destination.X - GetActorLocation().X) > 0 ? 0 : 180, 0.f));
	//如果移动组件已有效性
	if (MyMovementComponent)
	{
		//激活移动组件开始移动
		MyMovementComponent->Activate();
		//根据移动方向设置移动向量
		MyMovementComponent->Velocity = FVector(MoveDirection * 60,0.f,0.f);
	}
	//定时器事件句柄
	FTimerHandle TimerHandle;
	//吃法定时器更新移动方向
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AGhostActor::UpdateTargetLocation,FMath::RandRange(5,10),true);
}

void AGhostActor::UpdateGhostState()
{
	//如果当前状态时移动  实现走路到冲刺状态切换
	if (CurrentGhostState == EGhostState::Walk)
	{
		//计算冲刺的反向位置
		if (FMath::Abs(GetActorLocation().X - TargetLocation.X) < 60.f && FMath::Abs(GetActorLocation().Z - TargetLocation.Z) > 1.f)
		{
			ChangeGhostState(EGhostState::Dash);
		}
	}else if (CurrentGhostState == EGhostState::Dash)//如果当前状态时冲刺  实现冲刺到冲刺走路状态切换
	{
		FVector NewDirection = (TargetLocation - GetActorLocation()).GetSafeNormal();
		//计算冲刺的反向位置
		if ((TargetLocation - GetActorLocation()).Length() < 10.f)
		{
			ChangeGhostState(EGhostState::Walk);
			//重置移动速度
			MyMovementComponent->Velocity = FVector(MoveDirection * 60,0.f,0.f);
			return;
		}
		//重置移动速度
		MyMovementComponent->Velocity = NewDirection * 60.f;
	}
}
