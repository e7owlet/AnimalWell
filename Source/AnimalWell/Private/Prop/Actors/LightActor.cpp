// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Actors/LightActor.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"


ALightActor::ALightActor()
{
	// 创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp0"));
	// 创建线和灯的渲染组件
	LineSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LineSpriteComp0"));
	LightSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LightSpriteComp0"));
	// 绑定线和灯的渲染组件到根组件上
	LineSpriteComp->SetupAttachment(RootComponent);
	LightSpriteComp->SetupAttachment(LineSpriteComp);
	// 设置根组件碰撞预设为Prop
	LineSpriteComp->SetCollisionProfileName(TEXT("Prop"));
	LightSpriteComp->SetCollisionProfileName(TEXT("Prop"));
}

// Called when the game starts or when spawned
void ALightActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 回中计算
	SwingSpeed += -SwingAngle * 0.02f;
	// 模拟摩擦力
	SwingSpeed *= 0.98f;
	// 移动 计算移动角度
	SwingAngle += SwingSpeed * DeltaTime * 60.f;          
    
	//判断下一帧角度设置的方向
	if (SwingAngle > 30) SwingAngle = 30, SwingSpeed *= -0.7f;
	if (SwingAngle < -30) SwingAngle = -30, SwingSpeed *= -0.7f;
    
	// 设置Actor的旋转角度
	SetActorRotation(FRotator(SwingAngle, 0, 0));
	// 查找到的所有遮罩的对象数组
	TArray<AActor*> OutActors;
	// 全局查找遮罩Actor
	UGameplayStatics::GetAllActorsOfClass(this,AStaticMeshActor::StaticClass(),OutActors);
	// 遍历超找到的遮罩数组
	for ( auto Mask :OutActors)
	{
		// 移动判断遮罩指针是否正确
		if (AStaticMeshActor* MaskActor = Cast<AStaticMeshActor>(Mask))
		{
			// 便利遮罩上的标签数组
			for (auto Tag :MaskActor->Tags)
			{
				// 移动判断当前遮罩的标签是否为Mask
				if (Tag == "Mask")
				{
					// 获取当前组件上的模型组件
					UStaticMeshComponent* MeshComponent = MaskActor->GetStaticMeshComponent();
					//获取灯组件在世界场景中的位置
					FVector LightPosion = LightSpriteComp->GetComponentLocation();
					//更新材质表现
					MeshComponent->SetVectorParameterValueOnMaterials(MName,LightPosion);
				}
			}
		}
	}
}

void ALightActor::ActionEvent(FVector BeginLoaction)
{
	//判断传入的位置的左右方向
	if (BeginLoaction.X > GetActorLocation().X)
		SwingSpeed -= 10.0f;  //设置移动方向及速度
	else
		SwingSpeed += 10.0f; //设置移动方向及速度
}

void ALightActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//加载灯和线的资产
	UPaperSprite* LineSprite = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Line.PS_Line'"));
	UPaperSprite* LigthSprite = LoadObject<UPaperSprite>(this,TEXT("/Script/Paper2D.PaperSprite'/Game/Prop/Textures/Sprites/PS_Light.PS_Light'"));
	// 判断等和线资产是否有效
	if (LineSprite && LigthSprite)
	{
		//灯和线的资产设置
		LineSpriteComp->SetSprite(LineSprite);
		LightSpriteComp->SetSprite(LigthSprite);
		// 设置灯和线的相对位置
		LineSpriteComp->SetRelativeLocation(FVector(0, 0, LineSprite->GetSourceSize().Y/-2)) ;
		LightSpriteComp->SetRelativeLocation(FVector(0, 0.1, LineSprite->GetSourceSize().Y/-2)) ;
	}	
}


