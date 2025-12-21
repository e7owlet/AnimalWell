// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Framework/TestPropHUD.h"

#include "Blueprint/UserWidget.h"
#include "Prop/UMG/TestPropUserWidget.h"


void ATestPropHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowTestPropWidget();
}

void ATestPropHUD::ShowTestPropWidget()
{

	if (!TPWidget)
	{
		TSubclassOf<UTestPropUserWidget> Class = LoadClass<UTestPropUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Prop/UMG/UI_TestProp.UI_TestProp_C'"));
		if (!Class)
			return;
		TPWidget = CreateWidget<UTestPropUserWidget>(GetOwningPlayerController(),Class.Get());
	}
	if (!TPWidget->IsInViewport())
	{
		TPWidget->AddToViewport();
	}
}
