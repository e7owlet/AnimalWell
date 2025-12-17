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

	TWeakObjectPtr<class AMenuHUD> OwningHUD;	//存储传进来的AMenuHUD

	virtual bool SupportsKeyboardFocus() const override
	{
		return true;
	}	//允许这个Widget接收键盘焦点，block掉无用报错

};
