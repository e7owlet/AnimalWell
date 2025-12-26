// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/FirecrackerActor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Particles/ParticleSystem.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleEmitter.h"
#include "Prop/Actors/GhostActor.h"

// Sets default values
AFirecrackerActor::AFirecrackerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//根组件初始化
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	//根渲染组件初始化
	FirecrackerSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>("FirecrackerSpriteComp");
	//渲染组件绑定到根组件上
	FirecrackerSpriteComp->SetupAttachment(this->RootComponent);
	//设置渲染大小
	FirecrackerSpriteComp->SetRelativeScale3D(FVector(0.2f));
	//关闭渲染组件的碰撞
	FirecrackerSpriteComp->SetCollisionProfileName(TEXT("NoCollision"));

	//创建碰撞组件对象
	FirecrackerCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("FirecrackerCollisionComponent");
	//绑定碰撞组件到渲染组件上
	FirecrackerCollisionComponent->SetupAttachment(this->FirecrackerSpriteComp);
	//设置碰撞检测可以和所有组件发生重叠
	FirecrackerCollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	//胶囊体半径大小
	FirecrackerCollisionComponent->SetCapsuleRadius(32.f);
	//设置胶囊体半高
	FirecrackerCollisionComponent->SetCapsuleHalfHeight(64.f);
	//胶囊体在游戏开始后不可见
	FirecrackerCollisionComponent->bHiddenInGame = false;

	//初始化翻转组件
	MyRotatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovementComponent");
	//设置翻转组件旋转速度
	MyRotatingMovementComp->RotationRate = FRotator(500.f,0,0);
	//设置激活状态
	MyRotatingMovementComp->bAutoActivate = false;

	//创建抛物线移动组件
	MyProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	//初始速度为500
	MyProjectileMovementComp->InitialSpeed = 500.f;
	//最大移动速度为500
	MyProjectileMovementComp->MaxSpeed = 500.f;
	//重力影响系数为1 
	MyProjectileMovementComp->ProjectileGravityScale = 1.f;
	//设置组件为不激活
	MyProjectileMovementComp->bAutoActivate = false;
	
}

// Called when the game starts or when spawned
void AFirecrackerActor::BeginPlay()
{
	Super::BeginPlay();

}

//爆炸销毁
void AFirecrackerActor::DestroyFirecracker()
{
	//关闭旋转组件
	MyRotatingMovementComp->Deactivate();
	//关闭移动组件
	MyProjectileMovementComp->Deactivate();
	//加载爆炸效果美术资产
	UParticleSystem * Boom = LoadObject<UParticleSystem>(this,TEXT("/Script/Engine.ParticleSystem'/Game/Prop/Particles/PS_Explosion_Air_Big_03.PS_Explosion_Air_Big_03'"));
	//创建爆照效果美术资产
	UGameplayStatics::SpawnEmitterAtLocation(this,Boom,GetActorLocation());
	//查找地图中的蓝鬼
	AGhostActor* Ghost = Cast<AGhostActor>( UGameplayStatics::GetActorOfClass(this,AGhostActor::StaticClass()));
	//判断蓝鬼与角色的距离
	if (Ghost&&(GetActorLocation() - Ghost->GetActorLocation()).Length() < 150.f)
	{
		//销毁蓝鬼
		Ghost->Destroy();
	}
	//销毁投掷物爆竹
	Destroy();
}	

// Called every frame
void AFirecrackerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AFirecrackerActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	//判断渲染资产是否已经加载
	if (!FirecrackerSprite)
	{
		//没有加载的话 加载资产
		FirecrackerSprite = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Cracker.PS_Cracker'"));
	}
	//如果资产不为空
	if (FirecrackerSprite)
	{
		//给渲染组件设置渲染资产
		FirecrackerSpriteComp->SetSprite(FirecrackerSprite);
	}
}


void AFirecrackerActor::ActionEvent(FVector BeginLoaction)
{
	//设置当前移动的方向
	SetActorRotation(BeginLoaction.Rotation());
	
	//激活旋转组件
	MyRotatingMovementComp->Activate();
	//激活移动组件
	MyProjectileMovementComp->Activate();
	//定时器记录爆竹爆炸时间
	GetWorld()->GetTimerManager().SetTimer(CrackerHandle,this,&AFirecrackerActor::DestroyFirecracker,0.5f,false);
	
}

