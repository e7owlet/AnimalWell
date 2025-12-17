// Fill out your copyright notice in the Description page of Project Settings.

//UI界面实现
#include "SMenuWidget.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SMenuWidget::Construct(const FArguments& InArgs)
{
	const FMargin ContentPadding = FMargin(500.0f, 300.0f);	//按钮内容边距

	const FText TitleText = LOCTEXT("GameTitle", "Animal Well");	//标题文本

	ChildSlot
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
						.ColorAndOpacity(FColor::Black)		//纯黑背景
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(ContentPadding)
				[
					SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						[
							SNew(STextBlock)
								.Text(TitleText)	//标题文本
						]
				]
		];
}

#undef LOCTEXT_NAMESPACE