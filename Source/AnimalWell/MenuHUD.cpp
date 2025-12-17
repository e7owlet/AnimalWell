// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuHUD.h"
#include "SMenuWidget.h"
#include "Widgets/SWeakwidget.h"
#include "Engine/Engine.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine && GEngine->GameViewport) {
		MenuWidget = SNew(SMenuWidget)
			.OwningHUD(this);	//传入自身指针以便调用HUD里的函数

		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));	//将菜单UI Widget添加到Viewport
	}
}