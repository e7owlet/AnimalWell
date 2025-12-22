// Fill out your copyright notice in the Description page of Project Settings.

//UI界面实现
#include "SMenuWidget.h"
#include "MenuHUD.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/InputSettings.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SSlider.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Images/SImage.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SMenuWidget::Construct(const FArguments& InArgs)
{
	bCanChildrenBeAccessible = true;	//允许子控件被辅助功能访问

	OwningHUD = InArgs._OwningHUD;	//存储传进来的AMenuHUD指针

	const FMargin ContentPadding = FMargin(500.0f, 300.0f);	//按钮内容边距
	const FMargin ButtonPadding = FMargin(10.0f);		//按钮间距

	const FText TitleText = LOCTEXT("GameTitle", "Animal Well");	//标题文本，LOCTEXT便于本地化
	const FText PlayText = LOCTEXT("PlayGame", "Play");				//开始
	const FText SettingsText = LOCTEXT("Settings", "Settings");		//设置
	const FText QuitText = LOCTEXT("QuitGame", "Quit Game");		//退出

	FSlateFontInfo ButtonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");	//文本字体
	ButtonTextStyle.Size = 40.0f;	//文本字体大小
	FSlateFontInfo TitleTextStyle = ButtonTextStyle;
	TitleTextStyle.Size = 60.0f;	//标题字体大小

	//构造键位列表内容（提前构建）
	TSharedRef<SVerticalBox> KeysBox = SNew(SVerticalBox);
	const UInputSettings* InputSettings = GetDefault<UInputSettings>();
	if (InputSettings)
	{
		//显示动作映射列表
		KeysBox->AddSlot().AutoHeight()[ SNew(STextBlock).Text(LOCTEXT("KeyBindingsLabel", "Key Bindings:")) ];
		for (const FInputActionKeyMapping& Mapping : InputSettings->GetActionMappings())
		{
			FText Line = FText::FromString(FString::Printf(TEXT("%s : %s"), *Mapping.ActionName.ToString(), *Mapping.Key.GetDisplayName().ToString()));
			KeysBox->AddSlot().AutoHeight()[ SNew(STextBlock).Text(Line) ];
		}
	}

	ChildSlot
	[
		//保存顶层 overlay 到 RootOverlay，之后可以继续向其添加槽
		SAssignNew(RootOverlay, SOverlay)

		//背景
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Black)
		]

		//主面板（当显示设置时隐藏主面板）
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(ContentPadding)
		[
			SNew(SBox)
			.Visibility(TAttribute<EVisibility>::CreateLambda([this]() { return bShowingSettings ? EVisibility::Collapsed : EVisibility::Visible; }))
			[
				SNew(SVerticalBox)

				//标题
				+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.Font(TitleTextStyle)
					.Text(TitleText)
					.Justification(ETextJustify::Center)
				]

				//开始
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMenuWidget::OnPlayClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(PlayText)
						.Justification(ETextJustify::Center)
					]
				]

				//设置（切换到设置面板）
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMenuWidget::OnSettingsClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(SettingsText)
						.Justification(ETextJustify::Center)
					]
				]

				//退出
				+ SVerticalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					.OnClicked(this, &SMenuWidget::OnQuitClicked)
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(QuitText)
						.Justification(ETextJustify::Center)
					]
				]
			]
		]

		//设置面板（覆盖主面板）
		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SBox)
			.WidthOverride(800)
			.HeightOverride(600)
			.Visibility(TAttribute<EVisibility>::CreateLambda([this]() { return bShowingSettings ? EVisibility::Visible : EVisibility::Collapsed; }))
			[
				SNew(SBorder)
				.Padding(FMargin(20))
				[
					SNew(SVerticalBox)

					//面板标题
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock)
						.Font(ButtonTextStyle)
						.Text(LOCTEXT("SettingsTitle", "Settings"))
						.Justification(ETextJustify::Center)
					]

					//亮度标签
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(FMargin(0,20,0,10))
					[
						SNew(STextBlock)
						.Text(LOCTEXT("BrightnessLabel", "Brightness"))
					]

					//亮度滑块（初始值从 HUD 读取，如无 HUD 则 1.0）
					+ SVerticalBox::Slot()
					.AutoHeight()
					.Padding(FMargin(0,0,0,10))
					[
						SNew(SSlider)
						.Value(OwningHUD.IsValid() ? OwningHUD->GetCurrentScreenBrightness() * 0.5f : 0.5f) // 将 [0..2] 映射到 [0..1] 滑块范围
						.OnValueChanged(this, &SMenuWidget::OnBrightnessChanged)
					]

					//键位滚动区（把预先构造的 KeysBox 放进来）
					+ SVerticalBox::Slot()
					.FillHeight(1.0f)
					.Padding(FMargin(0,10,0,10))
					[
						SNew(SScrollBox)
						+ SScrollBox::Slot()
						[
							KeysBox
						]
					]

					//返回按钮（返回主菜单）
					+ SVerticalBox::Slot()
					.AutoHeight()
					.HAlign(HAlign_Right)
					.Padding(FMargin(0,10,0,0))
					[
						SNew(SButton)
						.OnClicked_Lambda([this]() -> FReply { bShowingSettings = false; return FReply::Handled(); })
						[
							SNew(STextBlock).Text(LOCTEXT("Back", "Back"))
						]
					]
				]
			]
		]
	];
}

FReply SMenuWidget::OnPlayClicked() const
{
	if (OwningHUD.IsValid()) {
		OwningHUD->RemoveMenu();
	}
	return FReply::Handled();
}

FReply SMenuWidget::OnSettingsClicked()
{
	//模仿 Start/Quit 的显示/隐藏操作：显示设置并隐藏主菜单
	bShowingSettings = true;
	return FReply::Handled();
}

void SMenuWidget::OnBrightnessChanged(float NewValue)
{
	//滑块值为 [0..1]，映射到亮度 [0..2]
	const float Brightness = FMath::Clamp(NewValue * 2.0f, 0.0f, 2.0f);
	if (OwningHUD.IsValid())
	{
		OwningHUD->SetScreenBrightness(Brightness);
	}
}

FReply SMenuWidget::OnQuitClicked() const
{
	if (OwningHUD.IsValid()) {
		if (APlayerController* PC = OwningHUD->PlayerOwner) {
			PC->ConsoleCommand("quit");
		}
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE