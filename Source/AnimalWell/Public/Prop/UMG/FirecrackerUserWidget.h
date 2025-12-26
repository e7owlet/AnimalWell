// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FirecrackerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANIMALWELL_API UFirecrackerUserWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
	//绑定页面爆竹的剩余数量
	UPROPERTY(EditAnywhere,meta = (BindWidget))
	class UTextBlock * CrackerCount;
	//绑定爆竹图片组件
	UPROPERTY(EditAnywhere,meta = (BindWidgetAnim),Transient)
	class UWidgetAnimation * ImageAnim;
	//设UI上炮竹显示数量
	void SetCrackerCount(int32 CrackerCount);
	//炮竹数量不足时播放UI动画
	void Play0Animation();
};
	