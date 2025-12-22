// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class SMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMenuWidget) {}

	SLATE_ARGUMENT(TWeakObjectPtr<class AMenuHUD>, OwningHUD)	//把AMenuHUD传进来，以便调用HUD里的函数

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	FReply OnPlayClicked() const;
	FReply OnQuitClicked() const;

	//Settings 相关
	FReply OnSettingsClicked();
	void OnBrightnessChanged(float NewValue);

	TWeakObjectPtr<class AMenuHUD> OwningHUD;	//存储传进来的AMenuHUD

	//是否正在显示设置面板
	bool bShowingSettings = false;

	//保存顶层 Overlay 的引用（便于构造后操作）
	TSharedPtr<class SOverlay> RootOverlay;

	virtual bool SupportsKeyboardFocus() const override
	{
		return true;
	}	//允许这个Widget接收键盘焦点，抑制相关警告
};
