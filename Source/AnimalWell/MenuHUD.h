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
	TSharedPtr<class SMenuWidget> MenuWidget;	//菜单UI Widget指针
	TSharedPtr<class SWidget> MenuWidgetContainer; //菜单UI Widget容器指针

	virtual void BeginPlay() override;
};
