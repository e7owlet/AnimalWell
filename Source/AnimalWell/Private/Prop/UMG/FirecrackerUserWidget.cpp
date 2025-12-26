// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/UMG/FirecrackerUserWidget.h"

#include "Components/TextBlock.h"

void UFirecrackerUserWidget::SetCrackerCount(int32 Count)
{
	//设置炮竹显示数量
	CrackerCount->SetText(FText::FromString(FString::FromInt(Count)));
}

void UFirecrackerUserWidget::Play0Animation()
{
	//播放UI动画
	PlayAnimationForward(ImageAnim,10.f);
}
