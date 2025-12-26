// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Components/InteractionPropComponent.h"


#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Prop/Actors/CandleActor.h"
#include "Prop/Actors/FirecrackerActor.h"
#include "Prop/Actors/FirecrackerScenePropActor.h"
#include "Prop/Actors/LightActor.h"
#include "Prop/Actors/ToggerActor.h"
#include "Prop/UMG/FirecrackerUserWidget.h"

// Sets default values for this component's properties
UInteractionPropComponent::UInteractionPropComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInteractionPropComponent::BeginPlay()
{
	Super::BeginPlay();
	//游戏开始时保存角色指针
	CharacterInstance = Cast<ACharacter>(GetOwner());
	//显示蜡烛数量UI
	ShowFirecrackerCount();
}


// Called every frame
void UInteractionPropComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//向前检测事件触发
	TracePropForword();
	//向后检测事件触发
	TracePropBack();
	//记录按键
	BindKeyDownEvent();
	//检测开关，蜡烛与爆竹
	TracePropToggleAndFirecrackerAndCandle();
}

void UInteractionPropComponent::TracePropForword()
{
	//检测物品数组
	TArray<FHitResult> OutHits;
	//碰撞影响参数
	FCollisionQueryParams Params;
	//设置忽略角色检测
	Params.AddIgnoredActor(CharacterInstance);
	//计算检测起点
	FVector StartLocation = 
		CharacterInstance->GetActorLocation()+CharacterInstance->GetActorUpVector()*10;
	//计算检测终点
	FVector EndLocation = 
		StartLocation + CharacterInstance->GetActorForwardVector()*13.f+CharacterInstance->GetActorUpVector()*10;
	//发起射线检测
	GetWorld()->LineTraceMultiByChannel(OutHits,StartLocation,EndLocation,ECollisionChannel::ECC_GameTraceChannel1,Params);
	//遍历射线检测到对象的数组
	for (FHitResult &HitResult : OutHits)
	{
		//安全性校验  是否发生碰撞
		if (!HitResult.bBlockingHit) 
			return;
		//判断是否为灯类型
		ALightActor* Light = Cast<ALightActor>(HitResult.GetActor());
		if (Light)
		{
			//计算角色与灯碰撞的相对方向
			FVector Location = Light->GetActorLocation()-CharacterInstance->GetActorLocation().Normalize();
			//调用灯的触发函数，让灯摇晃
			Light->ActionEvent(Location);
		}
	}
}

void UInteractionPropComponent::TracePropBack()
{
	//检测物品数组
	TArray<FHitResult> OutHits;
	//碰撞影响参数
	FCollisionQueryParams Params;
	//设置忽略角色检测
	Params.AddIgnoredActor(CharacterInstance);
	//计算检测起点
	FVector StartLocation = 
		CharacterInstance->GetActorLocation()+CharacterInstance->GetActorUpVector()*10;
	//计算检测终点
	FVector EndLocation = 
		StartLocation + CharacterInstance->GetActorForwardVector()*-13.f+CharacterInstance->GetActorUpVector()*10;
	//发起射线检测
	GetWorld()->LineTraceMultiByChannel(OutHits,StartLocation,EndLocation,ECollisionChannel::ECC_GameTraceChannel1,Params);
	//遍历射线检测到对象的数组
	for (FHitResult &HitResult : OutHits)
	{
		//安全性校验  是否发生碰撞
		if (!HitResult.bBlockingHit) 
			return;
		//判断是否为灯类型
		ALightActor* Light = Cast<ALightActor>(HitResult.GetActor());
		if (Light)
		{
			//计算角色与灯碰撞的相对方向
			FVector Location = Light->GetActorLocation()-CharacterInstance->GetActorLocation().Normalize();
			//调用灯的触发函数，让灯摇晃
			Light->ActionEvent(Location);
		}
	}
}

void UInteractionPropComponent::TracePropToggleAndFirecrackerAndCandle()
{
	//检测物品数组
	TArray<FHitResult> OutHits;
	//碰撞影响参数
	FCollisionQueryParams Params;
	//设置忽略角色检测
	Params.AddIgnoredActor(CharacterInstance);
	//计算检测起点
	FVector StartLocation = 
		CharacterInstance->GetActorLocation();
	//计算检测终点
	FVector EndLocation = 
		StartLocation + CharacterInstance->GetActorUpVector()*-100.f;
	//发起射线检测
	GetWorld()->LineTraceMultiByChannel(OutHits,StartLocation,EndLocation,ECollisionChannel::ECC_GameTraceChannel1,Params);
	//遍历射线检测到对象的数组
	for (FHitResult &HitResult : OutHits)
	{
		//安全性校验  是否发生碰撞
		if (!HitResult.bBlockingHit) 
			return;
		//判断是否为开关类型
		AToggerActor* Togger = Cast<AToggerActor>(HitResult.GetActor());
		if (Togger)
		{
			//直接触发开关的交互逻辑
			Togger->ActionEvent();
		}
		//判断是否为爆竹类型
		AFirecrackerScenePropActor* Firecracker = Cast<AFirecrackerScenePropActor>(HitResult.GetActor());
		if (Firecracker)
		{
			//增加炮竹数量
			FirecrackerCount ++ ;
			//更新UI页面炮竹数量
			FirecrackerWidget->SetCrackerCount(FirecrackerCount);
			//触发场景道具爆竹呗检测的到后需要执行的事件
			Firecracker->ActionEvent();
		}
		//判断是否为蜡烛类型
		ACandleActor* Candle = Cast<ACandleActor>(HitResult.GetActor());
		if (Candle)
		{
			//调用拉叔的触发事件
			Candle->ActionEvent();
		}
	}
}





void UInteractionPropComponent::BindKeyDownEvent()
{
	//获取玩家控制器
	APlayerController * PC =  Cast<APlayerController>(CharacterInstance->GetController());
	//检查是否按下D
	if (PC&&PC->WasInputKeyJustPressed(EKeys::D))
	{
		bPressD = true;
	}
	//检查是否松开D
	if (PC&&PC->WasInputKeyJustReleased(EKeys::D))
	{
		bPressD = false;
	}
	//检测是否按下A
	if (PC&&PC->WasInputKeyJustPressed(EKeys::A))
	{
		bPressA = true;
	}
	//检查是否松开A
	if (PC&&PC->WasInputKeyJustReleased(EKeys::A))
	{
		bPressA = false;
	}
	//检查是否按下Y和D按键同时按下
	if (PC && PC->WasInputKeyJustPressed(EKeys::Y)&&bPressD)
	{
		//爆竹的数量如果==0 播放UI动画
		if (FirecrackerCount == 0)
		{
			FirecrackerWidget->Play0Animation();
		}
		//如果爆竹不等于0
		if (FirecrackerCount !=0)
		{
			//炮竹数量-1
			FirecrackerCount--;
			//创建可投掷的炮竹
			AFirecrackerActor * Firecracker =  
			GetWorld()->SpawnActor<AFirecrackerActor>(CharacterInstance->GetActorLocation(),FRotator(30,0,0));
			Firecracker->ActionEvent(FRotator(30,0,0).Vector());
			//刷新炮竹UI上显示的数量
			FirecrackerWidget->SetCrackerCount(FirecrackerCount);
		}
		
	}
	if (PC && PC->WasInputKeyJustPressed(EKeys::Y)&&bPressA)
	{
		if (FirecrackerCount == 0)
		{
			FirecrackerWidget->Play0Animation();
		}
		if (FirecrackerCount > 0)
		{
			FirecrackerCount--;
			AFirecrackerActor * Firecracker =  
				GetWorld()->SpawnActor<AFirecrackerActor>(CharacterInstance->GetActorLocation(),FRotator(150,0,0));
			Firecracker->ActionEvent(FRotator(150,0,0).Vector());
			FirecrackerWidget->SetCrackerCount(FirecrackerCount);
		}
		
	}
}

void UInteractionPropComponent::ShowFirecrackerCount()
{

	UClass* Widget = LoadClass<UFirecrackerUserWidget>(this,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Prop/UMG/UI_Firecracker.UI_Firecracker_C'"));
	
	FirecrackerWidget = CreateWidget<UFirecrackerUserWidget>(Cast<APlayerController>(CharacterInstance->GetController()),Widget);
	FirecrackerWidget->AddToViewport();
}

