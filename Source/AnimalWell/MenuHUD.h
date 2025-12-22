// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API AMenuHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	TSharedPtr<class SWidget> MenuWidgetContainer; //菜单 UI Widget 容器指针
	TSharedPtr<class SMenuWidget> MenuWidget;	//菜单 UI Widget 指针

	virtual void BeginPlay() override;

public:
	void ShowMenu();
	void RemoveMenu();

	//设置并应用画面亮度
	void SetScreenBrightness(float NewBrightness);

	//供 SMenuWidget 读取当前亮度
	float GetCurrentScreenBrightness() const { return CurrentScreenBrightness; }

private:
	//当前存储的亮度值，默认 1.0
	float CurrentScreenBrightness = 1.0f;
};
