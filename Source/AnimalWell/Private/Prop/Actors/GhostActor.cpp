// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/GhostActor.h"

#include "paperflipbookcomponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"



// Sets default values
AGhostActor::AGhostActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//根组件、渲染组件初始化
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RenderGhost = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("RenderGhostComp"));
	RenderGhost->SetupAttachment(RootComponent);

	//碰撞检测初始化、碰撞预设
	GhostCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("GhostCollisionComponent");
	GhostCollisionComponent->SetupAttachment(RenderGhost);
	GhostCollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	//碰撞体大小
	GhostCollisionComponent->SetCapsuleRadius(72.f);
	GhostCollisionComponent->SetCapsuleHalfHeight(144.f);
	GhostCollisionComponent->bHiddenInGame = true;

	//初始化移动组件
	MyMovementComponent  = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MyMovementComponent->InitialSpeed = 500.f;
	MyMovementComponent->MaxSpeed = 500.f;
	//重力为 0，即直线运动
	MyMovementComponent->ProjectileGravityScale = 0.f;
	MyMovementComponent->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AGhostActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGhostActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateGhostState();
}

void AGhostActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//硬加载为渲染资产赋值
	if (!GhostFlipbook_Idle)
	{
		GhostFlipbook_Idle = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/PF_Ghost_Idle.PF_Ghost_Idle'"));
	}
	if (!GhostFlipbook_Walk)
	{
		GhostFlipbook_Walk = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/PF_Ghost_Walk.PF_Ghost_Walk'"));
	}
	if (!GhostFlipbook_Jump)
	{
		GhostFlipbook_Jump = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/PF_Ghost_Jump.PF_Ghost_Jump'"));
	}
	if (!GhostFlipbook_Dash)
	{
		GhostFlipbook_Dash = LoadObject<UPaperFlipbook>(this,TEXT("/Script/Paper2D.PaperFlipbook'/Game/Prop/PaperFlipbook/BlueWizardDash.BlueWizardDash'"));
	}

	//默认为idle
	RenderGhost->SetFlipbook(GhostFlipbook_Idle);
}

// 逻辑 : 蓝鬼状态切换，并且更换 flipbook
void AGhostActor::ChangeGhostState(EGhostState NewGhostState)
{
	CurrentGhostState = NewGhostState;
	RenderGhost->SetFlipbook(GetGhostFlipbook(CurrentGhostState));
}

//根据传入的状态返回对应的 flipbook 资产
UPaperFlipbook* AGhostActor::GetGhostFlipbook(EGhostState GhostState)
{
	UPaperFlipbook* TempFlipbook = nullptr;

	switch (GhostState)
	{
		case EGhostState::Idle:
			TempFlipbook = GhostFlipbook_Idle;
			break;
		case EGhostState::Walk:
			TempFlipbook = GhostFlipbook_Walk;
			break;
		case EGhostState::Jump:
			TempFlipbook = GhostFlipbook_Jump;
			break;
		case EGhostState::Dash:
			TempFlipbook = GhostFlipbook_Dash;
			break;
	}
	return TempFlipbook;
}

void AGhostActor::ActionEvent(FVector BeginLoaction)
{
	Super::ActionEvent(BeginLoaction);

	//用于测试，设置目的地（实际是  player 的 location）
	BeginLoaction = FVector(-1000.f,0,-500.f);
	
	//朝 beginlocation（这里应该叫destination） 移动
	GhostMove(BeginLoaction);
}

void AGhostActor::UpdateTargetLocation()
{
	GhostMove(FVector(-1000.f,0,-500.f));
}

void AGhostActor::GhostMove(FVector Destination)
{
	ChangeGhostState(EGhostState::Walk);

	TargetLocation = Destination;

	//设置小鬼朝向
	MoveDirection = (Destination.X - GetActorLocation().X) > 0 ? 1 : -1;
	SetActorRotation(FRotator(0.f, (Destination.X - GetActorLocation().X) > 0 ? 0 : 180, 0.f));

	if (MyMovementComponent)
	{
		MyMovementComponent->Activate();
		MyMovementComponent->Velocity = FVector(MoveDirection * 500,0.f,0.f);
	}
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AGhostActor::UpdateTargetLocation,FMath::RandRange(3,7),true);
}

void AGhostActor::UpdateGhostState()
{
	if (CurrentGhostState == EGhostState::Idle)
	{
		return;
	}else if (CurrentGhostState == EGhostState::Walk)
	{
		//朝目标移动中，在 x 分量插值小于 500 时俯冲
		if ((GetActorLocation().X - TargetLocation.X) < 500.f && (GetActorLocation().Z - TargetLocation.Z) > 10.f)
		{
			ChangeGhostState(EGhostState::Dash);
		}
	}else if (CurrentGhostState == EGhostState::Dash)
	{
		FVector NewDirection = (TargetLocation - GetActorLocation()).GetSafeNormal();
		//当达到目标时候，切换为 idle
		if ((TargetLocation - GetActorLocation()).Length() < 10.f)
		{
			ChangeGhostState(EGhostState::Walk);
			MyMovementComponent->Velocity = FVector(MoveDirection * 500,0.f,0.f);
			return;
		}
		MyMovementComponent->Velocity = NewDirection * 500.f;
	}
}
