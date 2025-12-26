// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/BasePropActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"

// Sets default values
ABasePropActor::ABasePropActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//创建基类中的碰撞盒子组件
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//根组件为碰撞组件
	RootComponent = CollisionBox;

	//设置碰撞预设为 场景交互
	CollisionBox->SetCollisionProfileName(TEXT("Prop"));

	//设置碰撞回调函数
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABasePropActor::OnOverlapBegin);



}

// Called when the game starts or when spawned
void ABasePropActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePropActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABasePropActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//判断碰撞对象是否有值或是否等于挂载者资深 满足进行碰撞事件调用
	if (OtherActor && (OtherActor != this))
	{
		 // 判断是否为玩家 
		APawn* PawnActor = Cast<APawn>(OtherActor);
		//如果是玩家
		if (PawnActor)
		{ //执行触发条件
			ActionEvent(PawnActor->GetActorLocation());
		}
	}
}



void ABasePropActor::ActionEvent(FVector BeginLoaction)
{
}

