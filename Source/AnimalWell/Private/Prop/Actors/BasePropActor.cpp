// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/BasePropActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"

// Sets default values
ABasePropActor::ABasePropActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// 创建碰撞盒，设为根组件
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	//设置碰撞属性，触发器模式，不阻挡玩家但能感应
	CollisionBox->SetCollisionProfileName(TEXT("Prop"));

	//当有东西重叠时，调用OnOverlapBegin
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

//碰撞后逻辑
void ABasePropActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//检查撞到的是不是玩家
	if (OtherActor && (OtherActor != this))
	{
		//尝试看看撞到的是不是一个Pawn，如果是则传入玩家位置
		APawn* PawnActor = Cast<APawn>(OtherActor);
		if (PawnActor)
		{
			ActionEvent(PawnActor->GetActorLocation());
		}
	}
}



void ABasePropActor::ActionEvent(FVector BeginLoaction)
{
	//空，给子类实现效果
	
}

