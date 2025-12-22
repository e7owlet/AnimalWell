// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "SMenuWidget.h"
#include "Engine/Engine.h"
#include "Widgets/SWeakWidget.h"
#include "GameFramework/PlayerController.h"

#include "Engine/PostProcessVolume.h"
#include "EngineUtils.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	ShowMenu();
}

void AMenuHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport) {
		MenuWidget = SNew(SMenuWidget).OwningHUD(this);	//传入自身指针以便调用HUD里的函数
		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));	//将菜单UI Widget添加到Viewport

		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = true;			//显示鼠标光标
			PlayerOwner->SetInputMode(FInputModeUIOnly());	//设置输入模式为仅UI
		}
	}
}

void AMenuHUD::RemoveMenu()
{
	if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid()) {
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());	//从Viewport移除菜单UI Widget
		if (PlayerOwner) {
			PlayerOwner->bShowMouseCursor = true;				//显示鼠标光标
			PlayerOwner->SetInputMode(FInputModeGameOnly());	//设置输入模式为仅游戏
		}
	}
}

void AMenuHUD::SetScreenBrightness(float NewBrightness)
{
	CurrentScreenBrightness = NewBrightness;

	UWorld* World = GetWorld();
	if (!World) {
		return;
	}

	//遍历场景中的所有后处理卷并修改 AutoExposureBias（运行时生效）
	for (TActorIterator<APostProcessVolume> It(World); It; ++It)
	{
		APostProcessVolume* PPV = *It;
		if (PPV)
		{
			PPV->Settings.AutoExposureBias = CurrentScreenBrightness;
		}
	}
}